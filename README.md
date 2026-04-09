# Modular Interaction System (Unreal Engine 5)

Proof of concept for a modular gameplay interaction framework built in Unreal Engine 5 using C++ and Blueprint integration.

## Overview

This system demonstrates a scalable, component-driven approach to handling player interactions with world objects such as doors, levers, and resource nodes. The goal is to avoid hardcoded interaction logic by centralizing detection while allowing each object to define its own behavior.

## Features

* Component-based interaction system (`UInteractionComponent`)
* Interface-driven execution (`INT_Interact`)
* Camera-based line trace interaction detection (Tick-driven)
* Decoupled interaction input and execution pipeline
* Dynamic UI prompt system (UMG)
* Reusable architecture for multiple interactable types

## Current Progress

* Base `InteractableActor` class (C++)
* `InteractionComponent` with exposed properties:

  * `bCanInteract`
  * `InteractionText`
* Interface-based interaction execution flow
* Player interaction trace system implemented (camera forward trace)
* Interaction input binding (`DoInteract`)
* Dynamic interaction prompt UI:

  * Widget created at runtime (`BeginPlay`)
  * Visibility driven by interaction trace
  * Displays context-sensitive interaction text

## Example Interactions

* Door → "Open Door"
* (Planned) Lever → "Pull Lever"
* (Planned) Resource Node → "Gather Resource"

## Technical Highlights

* Separation of responsibilities:

  * Detection (Character)
  * Validation (InteractionComponent)
  * Execution (Interface / Actor)
* Designed for extensibility without modifying core systems
* Blueprint-friendly for rapid iteration and designer control

## Next Steps

* Expand interaction types (lever, resource node, etc.)
* Improve UI system (animations, styling, input prompts)
* Add prioritization for multiple interactables
* Optimize trace logic if needed (distance/frequency tuning)
* Integrate with inventory or gameplay systems

## Purpose

This project is part of a gameplay programming portfolio, focusing on building scalable systems that reflect real-world game development practices.
