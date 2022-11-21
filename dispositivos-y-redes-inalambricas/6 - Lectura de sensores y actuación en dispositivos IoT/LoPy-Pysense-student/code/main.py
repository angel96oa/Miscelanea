#TODO:
#código en MicroPython necesario para la realización de la práctica.
# Ángel Ortega Alfaro

import pycom
import time
from pysense import Pysense
# humedad y temperatura
from SI7006A20 import SI7006A20
# luminosidad
from LTR329ALS01 import LTR329ALS01

py = Pysense()
li = LTR329ALS01(py)
si = SI7006A20(py)

pycom.heartbeat(False)
# Pongo el LED a rojo
pycom.rgbled(0xf0000)

while True:
    # Obtenemos valores
    temperatura = si.temperature()
    luminosidad = li.light()
    # Lo imprimimos por consola
    print("Temperatura: %d, Luminosidad: %d" % (temperatura, luminosidad[0]));

    # Comprobamos luminosidad y oscilamos LED
    if luminosidad[0] > 50:
        # LED a negro
        pycom.rgbled(0x000000)
    else:
        # LED a rojo
        pycom.rgbled(0xff0000)

    # Ejecuto el main cada segundo
time.sleep(1)
