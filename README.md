# MyContainer

A minimal Linux container runtime written from scratch in C.

The goal of this project is to understand how Linux containers actually work by implementing the core mechanisms ourselves instead of relying on Docker, Podman, containerd, or existing container runtimes.

This project is intended as a systems programming and Linux internals exercise.

---

## Project Goals

The final goal is to build a small container runtime capable of:

- Creating isolated processes
- Creating PID namespaces
- Creating UTS namespaces
- Creating mount namespaces
- Creating network namespaces
- Creating user namespaces
- Managing container resources with cgroups
- Configuring an isolated root filesystem
- Dropping Linux capabilities
- Executing processes inside the container
- Propagating container exit codes
- Eventually supporting a simplified OCI-style configuration

The project will be developed incrementally, with each milestone introducing a new Linux kernel feature.

---

## Architecture

The final runtime is expected to look approximately like this:

```text
                         mycontainer
                              |
              +---------------+---------------+
              |                               |
         Namespaces                         cgroups
              |                               |
      +-------+-------+               +-------+-------+
      |       |       |               |       |       |
     PID     UTS    Mount           Memory   CPU     PIDs
      |       |       |
    Network  User   Filesystem
      |       |       |
      +-------+-------+
              |
        Capabilities
              |
              v
           execve()
              |
              v
        Container process