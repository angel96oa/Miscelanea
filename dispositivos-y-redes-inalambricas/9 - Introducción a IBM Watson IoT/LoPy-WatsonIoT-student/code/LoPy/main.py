#TODO:
#código en MicroPython necesario para la realización de la práctica.

from network import WLAN
from pysense import Pysense
from LTR329ALS01 import LTR329ALS01
from MPL3115A2 import MPL3115A2, ALTITUDE, PRESSURE
from SI7006A20 import SI7006A20
from mqtt import MQTTClient
import machine
import pycom
import time
import ujson

py=Pysense()
li=LTR329ALS01(py) #Returns light level in lux.
si=SI7006A20(py)  #Return percentage relative humidity and temperature
pycom.heartbeat(False) #Stop automatc LED flashing

#Definición de funciones
def sub_cb(topic, msg):
    global mensajeVuelta
    mensajeVuelta = ujson.loads(msg)
    print(msg)


wlan = WLAN(mode=WLAN.STA)
wlan.connect("uclmiot", auth=(WLAN.WPA2, "zlX1zh3C5HYxhrcfQkF3"), timeout=5000)

print("Waiting to get connected to Wifi\n")
while not wlan.isconnected():
     machine.idle()
print("Connected to Wifi!\n")

#Conecto con broker
cliente = MQTTClient('d:bpgeee:LoPy4:my_first_device', 'bpgeee.messaging.internetofthings.ibmcloud.com',user='use-token-auth', password='s!hPTy2NGOC3XxHnk&', port=1883)
cliente.set_callback(sub_cb)
cliente.connect()
print("Connected to Watson IoT \n")

#Subscripción a topic
cliente.subscribe(topic="iot-2/cmd/Pycom/fmt/json")

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

    cliente.publish(topic="iot-2/evt/estados/fmt/json",msg=jsonstr)
    time.sleep(1)
    cliente.check_msg() #Chequeo si mensaje es recibido

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
