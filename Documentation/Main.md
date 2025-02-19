# Overview

Welcome to the documentation for Nuclide!

This is a software development kit (SDK) and development environment created by [Vera Visions, L.L.C.](https://www.vera-visions.com/). We want to share it with everyone to avoid duplicate effort and in the hopes that it is useful to someone else.

## What this project is {#what}

The Nuclide project produces a freely available game-logic component and 
development platform on top of [FTEQW](https://www.fteqw.org); which is the engine we happen to use.

The goal is to create a modern research base for new advancements, as well
as to have a stable base with a decent API for making games.

It comes with a simple example game (simply referred to as 'Base') and some test maps. There's also some other, third-party example projects.

General feature overview:

- SDK in the spirit of 'id Tech' development environments
- Client-side predicted movement, predicted weapons and vehicle systems
- Implementations of well known, established entity classes as seen in popular and critically acclaimed games
- Reference implementations for a lot of features exlusive to the FTEQW engine
- Designed to be familar to developers who are used to GoldSrc and Source engine
  project workflows
- Everything written from scratch with the modern QuakeC language advancements in mind

### 1. Why might I want to use it? {#why}

You might be migrating from an engine that is no longer being licensed and don't want to learn a new engine and toolchain.

You might want to develop a game using a lot of complex and well-tested objects
which might be tedious to implement on your own.

You might want to run or make modifications for a game using Nuclide and need full
control over what you can do.

### 2. How free is Nuclide? {#license}

Everything in Nuclide is **free software**. The copyright terms for the game-logic are
very permitting. Nuclide *does not use the GPL* as a point of reference in terms of license, it instead uses a **ISC-like license**. This means you can use, copy, modify and
distribute the code and work resulting from it for any purpose.

**Please read the very short 'LICENSE' document for details.**

### 3. What are the alternatives? {#alternatives}

Implementing systems such as prediction, complex map objects and entities on
your own, from scratch - or licensing another engine such as [Source](https://partner.steamgames.com/doc/sdk/uploading/distributing_source_engine) that ships with its own **Source SDK Base**.

### 4. Any example projects? {#examples}

- [The Wastes](https://store.steampowered.com/app/793670) is a commerical game built using Nuclide.
- [FreeHL](https://www.github.com/eukara/freehl) is a free-software, clean-room clone of Half-Life: Deathmatch also built using Nuclide.
- [FreeCS](https://www.github.com/eukara/freecs) exists in the same vein as FreeHL, but targetting a recreation of Counter-Strike v1.5 (mod version) specifically.

## Getting started {#prerequisites}

First of all, you want to be sure this is what you want to get into.
If you do posess a basic knowledge of the following:

- The C programming language
- Debugging a native application
- Makefiles
- Compiling your own binaries
- Concept of public and private APIs
- QuakeC

Then you will have a good time.
We strive to keep the codebase portable and conform to open standards wherever possible.
This means that if you develop on Windows, you probably want to install something like [Cygwin](https://www.cygwin.com/) to make this bearable.

Please don't ask us how to learn UNIX/Cygwin.

**This is a development kit and a development environment. This is not a game.**

## Actually getting started {#how}

You clone the Nuclide git repository first. There's multiple places to get it, one such place may be GitHub:

`git clone https://github.com/veravisions/nuclide`

And then you can [get started on building the engine and the rest of the toolchain](Building.md). Alternatively, you can also move in the official FTEQW binaries into the Nuclide directory to get started without bootstrapping your own engine + QuakeC compiler.