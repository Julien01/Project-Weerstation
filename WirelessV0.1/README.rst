.. _uart_sample:

UART Driver Sample
##################

Overview
********

This sample demonstrates how to use the UART serial driver with a simple
echo bot. It reads data from the console and echoes the characters back after
an end of line (return key) is received.

The polling API is used for sending data and the interrupt-driven API
for receiving, so that in theory the thread could do something else
while waiting for incoming data.

By default, the UART peripheral that is normally used for the Zephyr shell
is used, so that almost every board should be supported.

Building and Running
********************

Build and flash the sample as follows, changing ``nrf52840dk_nrf52840`` for
your board:

.. zephyr-app-commands::
   :zephyr-app: samples/drivers/uart/echo_bot
   :board: nrf52840dk_nrf52840
   :goals: build flash
   :compact:

Sample Output
=============

.. code-block:: console

    Hello! I\'m your echo bot.
    Tell me something and press enter:
    # Type e.g. "Hi there!" and hit enter!
    Echo: Hi there!

STM32 Nucleo f030 r8 notes
==========================

- use USART1 as uart; usart2 is used as debugging channel.
- in main use definition: #define UART_DEVICE_NODE DT_NODELABEL(usart1)
- no overlay is needed; default is usart1 enabled with following settings:
  - 115200 8N1
  - TX on PA9 (D8)
  - RX on PA10 (D2) 

- testing with USB->serial converter
  - black -> gnd
  - yellow(rx) to PA9
  - orange(tx) to PA10

build: west build -p auto -b nucleo_f030r8 <this directory>
flash: west flash


