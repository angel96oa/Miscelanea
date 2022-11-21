#TODO:
#código en MicroPython necesario para la realización de la práctica.

# Angel Ortega Alfaro y Alvaro Leon Cebrian

import machine
from network import WLAN
from pysense import Pysense
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2, ALTITUDE, PRESSURE
from SI7006A20 import SI7006A20
from mqtt import MQTTClient
import pycom
import time
import ujson

#Definición de variables entorno: Constantes
DEVICE_ID = "Pycom1"
# Cambiar por el valor del servidor
BROKER_IP = "xx.xx.xx.xx"

#Definición de funciones
def sub_cb(topic, msg):
    global mensajeVuelta
    mensajeVuelta = ujson.loads(msg)

wlan = WLAN(mode=WLAN.STA)
# cambiar por los valores de la ip del pc y del ap
wlan.ifconfig(config = ('xx.xx.xx.xx','xx.xx.xx.xx','xx.xx.xx.xx','xx.xx.xx.xx'))
wnets = wlan.scan()     #Escaneo
MOTE_STATE_MQTT_AUTO = False     #AUTO
MOTE_STATE_MQTT_MANUAL = True    #MANUAL
#Conexión a la Red
for net in wnets:
    # cambiar por el nombre de la red a la que se va a conectar
    if net.ssid == ' -- ':
        print('Network found!')
        # cambiar por la contraseña de la red a la que se va a conectar
        wlan.connect(net.ssid, auth=(net.sec, ' -- '), timeout=5000)
        while not wlan.isconnected():
            machine.idle() # save power while waiting
        print("Conectado al WIFI! \n")
        break


#Conecto con broker
client = MQTTClient(DEVICE_ID,BROKER_IP,port=1883)
client.set_callback(sub_cb)
client.connect()

#Subscripción a topic
client.subscribe(topic="Web/valores")

py=Pysense()
li=LTR329ALS01(py) #Returns light level in lux.
si=SI7006A20(py)  #Return percentage relative humidity and temperature
pycom.heartbeat(False) #Stop automatc LED flashing

datos = {
    'temperature' : "",
    'light' : ""
}

mensajeVuelta = {
    'estado' : False,
    'led' : False,
    'color' : "000000"
}

#Bucle infinito: Cuerpo programa
while True:
    datos['temperature'] = si.temperature() #Leo valores de temperatura
    datos['light'] = li.light() #Leo valores de luminosidad

    jsonstr = ujson.dumps(datos)
    print(jsonstr)
    time.sleep(1)

#Publico dato
    print("Sending ON")
    client.publish(topic="Pycom1/valores",msg=jsonstr)
    time.sleep(1)
    client.check_msg() #Chequeo si mensaje es recibido

    if not mensajeVuelta["estado"]: #AUTO
        if (datos["light"][0] <= 50):
            pycom.rgbled(int("0x" + (mensajeVuelta["color"])))
        else:
            pycom.heartbeat(False) #Led apagado

    else:                   #MANUAL
        if mensajeVuelta["led"]:
            pycom.rgbled(int("0x" + (mensajeVuelta["color"])))
        else:
            pycom.heartbeat(False) #Led apagado
