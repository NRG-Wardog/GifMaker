# GifMaker

[![CI](https://github.com/NRG-Wardog/GifMaker/actions/workflows/ci.yml/badge.svg)](https://github.com/NRG-Wardog/GifMaker/actions/workflows/ci.yml)

**C frame-sequence editor and playback project using linked data structures and OpenCV.**

GifMaker is an earlier systems/programming project from the Magshimim program. It manages an ordered sequence of image frames in C, supports editing and persistence of that sequence, and uses OpenCV for visual playback.

The repository is kept as evidence of **manual memory management, linked-structure invariants, file persistence, modular C code, native multimedia integration, and testable separation between core data logic and rendering**.

---

## Features

- Add frames to an animation sequence
- Remove frames safely, including empty-list cases
- Reorder frames with bounds/not-found protection
- Change per-frame or global display duration
- Save a project to disk
- Load and continue editing an existing project
- Render/play the frame sequence with OpenCV
- Interactive command-line editing flow
- Deterministic CI tests for the portable linked-list core

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
│ portable + tested│    │                      │
└────────┬─────────┘    └──────────┬───────────┘
         │                         │
         └────────────┬────────────┘
                      ▼
              ┌───────────────┐
              │  view.c/.h    │
              │ OpenCV render │
              └───────────────┘
```

The core list module no longer depends on OpenCV headers. Rendering remains behind the `play(...)` boundary, which allows the data-structure layer to compile and run tests on a minimal C toolchain.

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
├── tests/
│   └── test_linked_list.c
├── .github/workflows/
│   └── ci.yml
├── LICENSE
└── README.md
```

---

## Engineering Concepts Demonstrated

- C structs and pointers
- Dynamic allocation and ownership cleanup
- Linked-list insertion, removal, lookup, reordering, and mutation
- Defensive handling of empty/missing/invalid operations
- Separation of data structure, persistence, rendering, and CLI responsibilities
- File parsing and serialization
- Native library integration
- Portable unit testing of a subsystem from a Windows/OpenCV application
- Visual Studio C project organization

---

## Validation

The portable core can be tested without installing OpenCV:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror \
  -I GifMaker \
  GifMaker/linkedList.c tests/test_linked_list.c \
  -o linked-list-tests
./linked-list-tests
```

The test suite covers:

- empty-list operations;
- frame creation and lookup;
- per-frame and global duration changes;
- move-to-head / move-to-tail behavior;
- invalid move requests without list corruption;
- removal from the middle, head, and final node.

GitHub Actions runs the same build with warnings treated as errors.

---

## Full Application Build

The repository includes a Visual Studio solution under `GifMaker/GifMaker.sln`.

The full playback application depends on OpenCV. Build configuration may need to be adjusted to match the OpenCV installation available on the local machine.

A generic GCC-style full build has the following source shape:

```bash
gcc prog.c linkedList.c openAndEditProg.c view.c -o gif_maker <opencv-flags>
```

Run the command from the `GifMaker/` source directory and supply the OpenCV compiler/linker flags appropriate for the installed version.

---

## Project Status

This is a completed historical learning project rather than an actively maintained multimedia product. The core data-structure layer has been hardened and covered by CI while the original OpenCV application remains preserved as the historical project.

---

## Limitations

- Full playback still depends on the OpenCV/toolchain configuration used by the application environment
- Command-line editing rather than a modern GUI
- Rendering/persistence paths are not covered by the portable core CI suite
- Manual memory management requires explicit ownership discipline
- Not intended as a production GIF/video editing tool

---

## License

See [LICENSE](LICENSE).
