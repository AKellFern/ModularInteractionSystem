// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "InteractionFramework.h"



// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bCanInteract = true;

	InteractionText = FText::FromString(TEXT("Interact"));
}


void UInteractionComponent::ConfirmInteract()
{
	if (bCanInteract)
	{
		UE_LOG(LogInteractionFramework, Log, TEXT("Interaction confirmed on %s"), *GetNameSafe(this));

		AActor* Owner = GetOwner();

		if (Owner)
		{
			bool bImplemented = Owner->Implements<UINT_Interact>();

			if (bImplemented)
			{
				IINT_Interact::Execute_ExecuteInteraction(Owner);
			}
			else
			{
				UE_LOG(LogInteractionFramework, Warning, TEXT("Owner %s does not implement the interaction interface"), *GetNameSafe(Owner));
			}
		}
	}

}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

