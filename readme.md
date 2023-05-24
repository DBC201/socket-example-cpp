# Socket Example CPP

This is a simple example project that demonstrates a client-server communication using sockets. The project includes a server program and a client program written in C++. The server and client can exchange messages over a network connection.

## Features

- Server program: Listens on a specified port and echoes received messages back to the client.
- Client program: Connects to the server and allows the user to send messages and receive echoed messages.

## Prerequisites

- C++ compiler that supports C++20 standard
- CMake build system
- [Optional] Git (for version control)

## Build and Run

Follow the steps below to build and run the project:

1. Clone the repository:

```git clone git@github.com:DBC201/socket-example-cpp.git```

```cd socket-example```

2. Create a build directory and navigate into it:

```mkdir build```

```cd build```

3. Generate the build files using CMake:

```cmake ..```

4. Build the project:

```cmake --build .```

5. Run the server:

```./server```

6. In a separate terminal or command prompt, run the client:

```./client```

7. Enter messages in the client terminal and observe the echoed messages from the server.

---

## Summary of Prompts

1. Simple messaging protocol over sockets in C++
2. Server-side code implementation
3. Client-side code implementation
4. CMakeLists.txt file for compilation
5. .gitignore file for the project
6. README.md file for the project
7. Mention of AI language model's involvement

These prompts and interactions guided the development of the code, CMakeLists.txt, .gitignore, and README.md files, providing you with a functional socket-based client-server communication example project in C++.

---

Created with the assistance of an AI language model (ChatGPT) developed by OpenAI.
