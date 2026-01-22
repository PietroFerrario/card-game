# Deckbuilding Game Prototype (C++)

This repository contains an early-stage prototype of a videogame project developed in C++.

The current version uses a terminal-based interface to support rapid iteration on gameplay systems and internal architecture. The terminal presentation layer is not intended to represent the final form of the game.

At this stage, the project focuses on designing and validating core mechanics, system boundaries, and data flow before introducing a graphical frontend.

## Game Concept

This project is a prototype of a single-player, turn-based roguelike deckbuilding game.

Gameplay is centered around hand-based combat, where the player uses cards to perform actions, manage temporary effects, and reduce enemy HP through a structured turn loop.

Between combats, the player progresses through a branching story structure. Narrative events and choices modify the player’s deck, allowing cards to be added, removed, or transformed, shaping each run differently.

The project focuses on building a clean and extensible combat and progression foundation.

## Project Status
Development stage: early prototype (v0)

The project is under active development and should be considered experimental.
Features, structure, and APIs may change as gameplay systems evolve.

## Current Scope

The current implementation is intentionally minimal and includes:

- turn-based combat prototype
- deck-based card mechanics
- runtime card instantiation
- effect-driven gameplay logic
- terminal-based interaction layer

The purpose of this version is to verify correctness and extensibility of the gameplay systems rather than presentation or user experience.

## Long-Term Direction

The long-term goal of this project is to develop a complete videogame with a dedicated graphical interface.

The terminal version exists solely as a development and validation layer. All gameplay logic is written independently of the user interface so that a graphical frontend can be introduced later without rewriting core systems.

## Documentation

Source-level documentation is generated using Doxygen and is available through GitHub Pages.
Detailed class and system documentation is maintained in the generated documentation.