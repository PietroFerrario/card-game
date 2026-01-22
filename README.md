# Deckbuilding Game Prototype (C++)

Turn-based, roguelike-inspired deckbuilding game written in C++.

This repository contains an early-stage prototype focused on gameplay systems, internal architecture, and system boundaries.

The current implementation uses a terminal-based interface to allow rapid iteration and validation of mechanics.  
The terminal layer is not intended to represent the final presentation of the game.

## Documentation

Full source-level documentation is available here:

https://pietroferrario.github.io/card-game/

Documentation is generated using Doxygen and describes the architecture, class responsibilities, and system interactions.

## Game Concept

The project explores the design of a single-player, turn-based deckbuilding game inspired by roguelike mechanics.

Combat is centered around hand-based gameplay, where cards trigger effects, modify combat state, and interact through a structured turn loop.

Between combats, the player progresses through branching narrative events. These events influence the player’s deck by adding, removing, or transforming cards, shaping each run differently.

The primary goal is to build a clean, extensible foundation for combat and progression systems.

## Current Scope

The current prototype includes:

- turn-based combat system
- deck and hand management
- runtime card instantiation
- effect-driven gameplay logic
- terminal-based interaction layer

This version prioritizes clarity and extensibility over presentation.

## Project Status

**Development stage:** early prototype (v0)

The project is under active development.  
Structure, features, and APIs may evolve as gameplay systems mature.

## Long-Term Direction

The long-term objective is to develop a complete game with a dedicated graphical interface.

All gameplay logic is intentionally decoupled from the presentation layer, allowing a future graphical frontend to be introduced without rewriting core systems.

## License
Source code is publicly viewable for learning and review purposes.
See LICENSE for details.