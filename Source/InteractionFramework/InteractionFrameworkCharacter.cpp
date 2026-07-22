// Copyright Epic Games, Inc. All Rights Reserved.

#include "InteractionFrameworkCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractionFramework.h"
#include "InteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/InteractorComponent.h"
#include <InteractableActor.h>

AInteractionFrameworkCharacter::AInteractionFrameworkCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
}

void AInteractionFrameworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInteractionFrameworkCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AInteractionFrameworkCharacter::Look);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInteractionFrameworkCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AInteractionFrameworkCharacter::DoInteract);
	}
	else
	{
		UE_LOG(LogInteractionFramework, Error, TEXT("Failed to find Enhanced Input component on %s"), *GetNameSafe(this));
	}
}

void AInteractionFrameworkCharacter::BeginPlay()
{

	Super::BeginPlay();

	if (InteractionPromptClass)
	{
		InteractionPromptWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionPromptClass);

		if (InteractionPromptWidget)
		{
			InteractionPromptWidget->AddToViewport();
			InteractionPromptWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogInteractionFramework, Error, TEXT("Failed to create Interaction Prompt Widget from class %s"), *GetNameSafe(InteractionPromptClass));
		}
	}

	InteractorComponent->SetTraceOrigin(FollowCamera);
}

void AInteractionFrameworkCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AInteractionFrameworkCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AInteractionFrameworkCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AInteractionFrameworkCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AInteractionFrameworkCharacter::DoJumpStart()
{
	Jump();
}

void AInteractionFrameworkCharacter::DoJumpEnd()
{
	StopJumping();
}

void AInteractionFrameworkCharacter::DoInteract()
{
	if (IsValid(InteractorComponent))
	{
		InteractorComponent->Interact();
	}
	else
	{
		UE_LOG(LogInteractionFramework, Error, TEXT("InteractorComponent is invalid on %s"), *GetNameSafe(this));
	}
}

void AInteractionFrameworkCharacter::PerformInteractionTrace()
{
	CurrentInteractionComponent = nullptr;

	CurrentInteractionText = FText::GetEmpty();

	if (InteractionPromptWidget)
	{
		InteractionPromptWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	FVector TraceStart = FollowCamera->GetComponentLocation();
	FVector TraceEnd = TraceStart + (FollowCamera->GetForwardVector() * InteractionTraceDistance);

	FHitResult HitResult;

	bool bValidHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

	if (bValidHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor)
		{
			UInteractionComponent* InteractionComp = HitActor->FindComponentByClass<UInteractionComponent>();

			if (InteractionComp && InteractionComp->bCanInteract)
			{
				UE_LOG(LogInteractionFramework, Log, TEXT("Looking at interactable: %s"), *HitActor->GetName());

				CurrentInteractionComponent = InteractionComp;

				CurrentInteractionText = InteractionComp->InteractionText;


				if (InteractionPromptWidget)
				{
					InteractionPromptWidget->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
	}
}

void AInteractionFrameworkCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractorComponent)
	{
		if (InteractorComponent->GetCurrentInteractableActor())
		{
			UE_LOG(LogInteractionFramework, Warning, TEXT("Interactor found: %s"),
				*InteractorComponent->GetCurrentInteractableActor()->GetName());
		}
		else
		{
			UE_LOG(LogInteractionFramework, Warning, TEXT("Interactor found nothing"));
		}
	}

	const bool bHasInteractable = IsValid(InteractorComponent->GetCurrentInteractableActor());

	CurrentInteractionText = InteractorComponent->GetCurrentInteractionText();

	if (InteractionPromptWidget)
	{
		InteractionPromptWidget->SetVisibility(
			bHasInteractable
			? ESlateVisibility::Visible
			: ESlateVisibility::Hidden);
	}
}	