# STM32H7 Ethernet Telemetry Bridge (UART to TCP)

High-performance, modular UART/MAVLink-to-Ethernet TCP telemetry bridge implemented on **STM32H753ZI (Nucleo-H753ZI)** using LwIP Raw API.

## Features
- **Zero-Copy Memory Handling:** `SCB_DisableDCache()` applied to prevent Ethernet DMA cache coherency failure on STM32H7 series.
- **Non-blocking TCP Server:** Handles client connection and telemetry streaming over Port `5000`.
- **Interrupt-Driven UART Processing:** Minimal latency parsing for incoming telemetry packages.
- **Modular C Architecture:** Separated modules for TCP bridge (`tcp_telemetry_bridge`), telemetry parser (`telemetry_parser`), and status indication (`status_led`).

## Hardware & System Setup
- **MCU:** Nucleo-H753ZI (Cortex-M7 @ 480MHz)
- **Ethernet PHY:** Onboard LAN8742 (RMII)
- **Static IP Configuration:** `192.168.1.10` / Subnet: `255.255.255.0`
- **TCP Bridge Port:** `5000`
- **UART Interface:** USART1 (115200 Baud, 8N1)

## Architecture Overview
```text
[ Ground Control Station / PC ] 
               | (UDP/Serial Python Bridge)
               v
       [ USART1 RX (STM32H7) ]
               | (UART RX Interrupt)
               v
     [ telemetry_parser Module ]
               | (g_rx_buffer / Live Expressions)
               v
  [ tcp_telemetry_bridge Module ]
               | (LwIP Raw API / Ethernet DMA)
               v
  [ TCP Client (Hercules / GCS) ]  <=== (IP: 192.168.1.10 : 5000)