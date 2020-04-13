# az3166-metronome

An analog click signal visualization and counter with MxChip IoT devkit.

## Getting Started

1. Install tooling [IoT DevKit Development Environment](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-arduino-iot-devkit-az3166-get-started#prepare-the-development-environment). None of Azure vscode extensions are really required.
1. DON'T yet connect your board to USB
1. Start code with click-metronome.code-workspace
1. In vscode `F1 -> Arduino: Board Manager -> MXChip - Microsoft Azure IoT Developer Kit AZ3166`
    - Choose latest version, upgrade firmware
1. `F1 -> Arduino: Board Config -> Select Board: MXCHIP az3166`, upload method leave default (OpenOCD)
1. Connect the board.
1. In vscode `F1 -> Arduino: Upload` to build and upload the app to the board.
