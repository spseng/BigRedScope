# BigRedScope

Desktop app that combines WPILib NetworkTables with an Ultralight UI.

## Prerequisites
- Windows 10/11 x64
- Visual Studio 2022 (Desktop C++ workload) or MSVC Build Tools
- CMake 3.14+
- Ultralight SDK extracted into `SDK/` (already present in this repo)
- WPILib Desktop C++ (headers/libs) installed at `C:/Users/Public/wpilib/2025/cpp` (default)

If your WPILib path is different, edit `CMakeLists.txt` and update `WPILIB_ROOT` for Windows.

## Build (PowerShell)

```powershell
# From repo root
cmake -S . -B build
cmake --build build --config Release --parallel
cmake --install build --config Release
```

The install step places a runnable bundle at:

```
build/out/MyApp/
```

This folder contains `MyApp.exe`, Ultralight DLLs, and the `assets/` directory.

## Run

```powershell
Start-Process -FilePath "${PWD}\build\out\MyApp\MyApp.exe"
```

A window should open showing the contents of `assets/app.html`.

## Notes
- If you want to embed assets into the executable (no external `assets/` folder), set `SHOULD_EMBED_FILES` to `TRUE` in `CMakeLists.txt`. This will compile resources in and remove the runtime dependency on the `assets` folder.
- To use NetworkTables, uncomment the example in `src/main.cpp` and link WPILib topics in your app logic. WPILib headers/libs are already wired to the `MyApp` target.
