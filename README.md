# Modular Interaction System (Unreal Engine 5)

Proof of concept for a modular gameplay interaction framework built in Unreal Engine 5 using C++ with Blueprint integration.

## Overview

This system demonstrates a scalable, component-driven approach to player interaction. Rather than hardcoding behavior per object, interaction detection is centralized while individual actors define their own responses.

The result is a flexible and extensible framework that supports rapid iteration and clean integration across multiple gameplay scenarios.

Visual assets used in this project are sourced from the Unreal Engine Fab marketplace for prototyping purposes; all gameplay systems and architecture are original implementations.

## Features

* Component-based interaction system (`UInteractionComponent`)
* Interface-driven execution (`INT_Interact`)
* Camera-based line trace interaction detection (Tick-driven)
* Decoupled input → interaction execution pipeline
* Dynamic UI prompt system (UMG)
* Reusable architecture for multiple interactable types

## Current Implementation

* Base `InteractableActor` class (C++)
* `InteractionComponent` with exposed properties:
  * `bCanInteract`
  * `InteractionText`
* Interface-based interaction execution flow
* Player-driven interaction trace system (camera forward trace)
* Input binding via Enhanced Input (`DoInteract`)
* Dynamic interaction prompt UI:
  * Widget created at runtime (`BeginPlay`)
  * Visibility driven by trace detection
  * Displays context-sensitive interaction text
* Example resource interaction:
  * Ore nodes can be targeted and destroyed via interaction

## Example Interactions

* Door → "Open Door"
* (Planned) Lever → "Pull Lever"
* (Planned) Resource Node → "Gather Resource"

## Technical Highlights

* Clear separation of responsibilities:
  * Detection → Character (trace system)
  * Validation → `InteractionComponent`
  * Execution → Interface / Actor
* Fully decoupled interaction pipeline
* Designed for extensibility without modifying core systems
* Blueprint-friendly for rapid iteration and designer control

## Next Steps

* Expand interaction types (lever, resource node variations, etc.)
* Enhance UI system (animations, styling, input prompts)
* Add interaction prioritization (multiple targets)
* Introduce interaction states (hold, cooldown, multi-step)
* Optimize trace performance if needed
* Integrate with inventory or gameplay systems

## Purpose

This project serves as a gameplay programming portfolio piece, demonstrating the design and implementation of scalable, modular systems aligned with real-world game development practices.

## Asset Usage & Attribution

This project incorporates third-party assets sourced from the Unreal Engine Fab marketplace for visual demonstration and prototyping purposes.

All core systems—including the interaction framework, component architecture, and gameplay logic—are original implementations developed independently.

Third-party assets are used in accordance with their respective licensing terms and are not included for redistribution as part of this project.
