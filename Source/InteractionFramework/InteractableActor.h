// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InteractableComponent.h"
#include "Interfaces/Interactable.h"
#include "InteractableActor.generated.h"

UCLASS()
class INTERACTIONFRAMEWORK_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UInteractableComponent* InteractableComponent;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	
	
};
