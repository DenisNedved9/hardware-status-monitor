# Hardware Status Monitor

A lightweight C console tool for automated health monitoring and diagnostics of ground station subsystems.

## Problem & Purpose
Ground stations rely on multiple hardware components (receivers, transmitters, GPS, batteries) generating continuous telemetry data. Manually tracking subsystem health from raw logs is inefficient and prone to human error.

This tool solves this challenge by automatically:
- **Parsing telemetry logs:** Reads subsystem states, temperatures, and specific metrics (voltage, satellites, battery percentage).
- **Evaluating system health:** Applies a worst-case priority logic to determine overall status (`OK`, `WARNING`, `CRITICAL`).
- **Generating alerts & reports:** Counts active warnings/errors and outputs a clean diagnostic summary to the console and a report file.
