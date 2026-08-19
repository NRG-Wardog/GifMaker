# GifMaker

**C frame-sequence editor and playback project using linked data structures and OpenCV.**

GifMaker is an earlier systems/programming project from the Magshimim program. It manages an ordered sequence of image frames in C, supports editing and persistence of that sequence, and uses OpenCV for visual playback.

The repository is kept as evidence of early work with **manual memory management, linked structures, file persistence, modular C code, and native multimedia integration**.

---

## Features

- Add frames to an animation sequence
- Remove frames
- Reorder frames
- Change per-frame display duration
- Save a project to disk
- Load and continue editing an existing project
- Render/play the frame sequence with OpenCV
- Interactive command-line editing flow

---

## Architecture

```text
            ┌───────────────────┐
            │      prog.c       │
            │ CLI / user flow   │
            └─────────┬─────────┘
                      │
          ┌───────────┴───────────┐
          │                       │
          ▼                       ▼
┌──────────────────┐    ┌──────────────────────┐
│ linkedList.c/.h  │    │ openAndEditProg.c/.h│
│ frame ownership  │    │ save / load project  │
│ ordering/editing │    │ persistence          │
└────────┬─────────┘    └──────────┬───────────┘
         │                         │
         └────────────┬────────────┘
                      ▼
              ┌───────────────┐
              │  view.c/.h    │
              │ OpenCV render │
              └───────────────┘
```

---

## Repository Layout

```text
GifMaker/
├── GifMaker/
│   ├── prog.c
│   ├── linkedList.c
│   ├── linkedList.h
│   ├── openAndEditProg.c
│   ├── openAndEditProg.h
│   ├── view.c
│   ├── view.h
│   ├── photos/
│   ├── GifMaker.sln
│   └── Project1.vcxproj
├── LICENSE
└── README.md
```

---

## Engineering Concepts Demonstrated

- C structs and pointers
- Dynamic memory management
- Linked-list ownership and mutation
- Separation of data structure, persistence, rendering, and CLI responsibilities
- File parsing and serialization
- Native library integration
- Visual Studio C project organization

---

## Build

The repository includes a Visual Studio solution under `GifMaker/GifMaker.sln`.

The original project depends on OpenCV. Build configuration may need to be adjusted to match the OpenCV installation available on the local machine.

A generic GCC-style build has the following source shape:

```bash
gcc prog.c linkedList.c openAndEditProg.c view.c -o gif_maker <opencv-flags>
```

Run the command from the `GifMaker/` source directory and supply the OpenCV compiler/linker flags appropriate for the installed version.

---

## Project Status

This is a completed historical learning project rather than an actively maintained multimedia application. It is intentionally preserved because it shows the progression from foundational C/data-structure work into later C++ systems, endpoint-security, backend, and AI engineering projects.

---

## Limitations

- Depends on the OpenCV/toolchain configuration used by the original development environment
- Command-line editing rather than a modern GUI
- No automated test suite
- Manual memory management requires careful ownership discipline
- Not intended as a production GIF/video editing tool

---

## License

See [LICENSE](LICENSE).
