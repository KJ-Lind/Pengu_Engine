# Pengu Engine

## Prerequisites

Before building the project, ensure that **Conan 2** is installed on your machine.

If Conan 2 is already installed, you may proceed directly to the [Building the Project](#building-the-project) section. If not, please follow the installation guide first: [Install Conan 2](./docs/ConanInstall.md).

---

## Building the Project

To generate the Visual Studio solution, locate the `genproject.bat` file inside the `tools` folder at the root.

If the file is not present, please contact the engine maintainer to obtain a complete copy of the Engine with the batch file included.

Once confirmed, run `genproject.bat` by double-clicking it or executing it from the command line:

```bash
tools\genproject.bat
```

This will install all required dependencies via Conan and generate a Visual Studio solution (`.sln`) in the build directory. Open the solution in **Visual Studio 2022** to begin development.

---

## How to Use the Engine

For a full step-by-step guide on using Pengu Engine — including scene creation, scripting, and rendering — refer to the engine guide:

[Engine Guide](./docs/EngineGuide.md)