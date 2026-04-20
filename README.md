# Modular Interaction System (Unreal Engine 5)

Proof of concept for a modular gameplay interaction framework built in Unreal Engine 5 using C++ with Blueprint integration.

## Overview

This system demonstrates a scalable, component-driven approach to player interaction. Rather than hardcoding behavior per object, interaction detection is centralized while individual actors define their own responses through composition and interface-driven execution.

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
* Interface-based interaction execution flow (via `INT_Interact`)
* Player-driven interaction trace system (camera forward trace)
* Input binding via Enhanced Input (`DoInteract`)
* Dynamic interaction prompt UI:

  * Widget created at runtime (`BeginPlay`)
  * Visibility driven by trace detection
  * Displays context-sensitive interaction text
* Example resource interaction:

  * Ore nodes can be targeted and destroyed via interaction
* Example character-based interaction:

  * A third-party character asset was converted into an interactable companion by:

    * Attaching `UInteractionComponent`
    * Implementing `INT_Interact`
    * Defining custom behavior (AI follow) in Blueprint
  * No modification to the core interaction system was required

## Example Interactions

* Character → "Ask to Follow" (AI companion behavior)
* Lever → "Unlock" → updates connected door state ("Locked" → "Open")
* Resource Node → "Gather Resource" (Ore/Herb)

## Technical Highlights

* Clear separation of responsibilities:

  * Detection → Character (trace system)
  * Validation → `InteractionComponent`
  * Execution → Interface / Actor
* Fully decoupled interaction pipeline
* Designed for extensibility without modifying core systems
* Blueprint-friendly for rapid iteration and designer control
* Supports composition-based extension of non-native actors (e.g., third-party assets)

## Demonstration of Modularity

A key goal of this system is to support integration of new gameplay actors without requiring changes to existing systems.

This is demonstrated by successfully converting a third-party character asset—originally designed for player control—into an interactable AI companion using only composition and interface implementation.

This integration required:

* No changes to the player interaction system
* No changes to the core interaction component or interface logic
* No dependency on a shared base class (`InteractableActor`)

Instead, the actor was integrated by:

* Adding `UInteractionComponent` for interaction eligibility
* Implementing `INT_Interact` for behavior execution
* Defining custom logic (AI follow behavior) at the actor level

This validates that the system supports true modular integration and can accommodate a wide variety of actor types, including externally sourced assets.

This demonstrates that new gameplay actors can be integrated through composition rather than inheritance, enabling flexible and scalable system growth.

## Next Steps

* Expand interaction types (NPC state changes, etc.)
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