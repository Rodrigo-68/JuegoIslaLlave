// Copyright Epic Games, Inc. All Rights Reserved.

#include "JuegoIslaLlaveCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/InputSettings.h"
#include "Engine/Engine.h"

AJuegoIslaLlaveCharacter::AJuegoIslaLlaveCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AccesorioCercano = nullptr;
}

void AJuegoIslaLlaveCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UInputSettings* InputSettings = UInputSettings::GetInputSettings())
	{
		TArray<FInputActionKeyMapping> ExistingRecoger;
		InputSettings->GetActionMappingByName(TEXT("Recoger"), ExistingRecoger);
		if (ExistingRecoger.Num() == 0)
		{
			InputSettings->AddActionMapping(FInputActionKeyMapping(TEXT("Recoger"), EKeys::A));
		}

		TArray<FInputActionKeyMapping> ExistingSoltar;
		InputSettings->GetActionMappingByName(TEXT("Soltar"), ExistingSoltar);
		if (ExistingSoltar.Num() == 0)
		{
			InputSettings->AddActionMapping(FInputActionKeyMapping(TEXT("Soltar"), EKeys::SpaceBar));
		}
	}
}

void AJuegoIslaLlaveCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJuegoIslaLlaveCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJuegoIslaLlaveCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJuegoIslaLlaveCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJuegoIslaLlaveCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJuegoIslaLlaveCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJuegoIslaLlaveCharacter::TouchStopped);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AJuegoIslaLlaveCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Recoger", IE_Pressed, this, &AJuegoIslaLlaveCharacter::RecogerAccesorio);
	PlayerInputComponent->BindAction("Soltar", IE_Pressed, this, &AJuegoIslaLlaveCharacter::SoltarAccesorio);
}

void AJuegoIslaLlaveCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AJuegoIslaLlaveCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AJuegoIslaLlaveCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AJuegoIslaLlaveCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJuegoIslaLlaveCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJuegoIslaLlaveCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AJuegoIslaLlaveCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AJuegoIslaLlaveCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AFMAccesorio* Accesorio = Cast<AFMAccesorio>(OtherActor))
	{
		if (!Accesorio->IsHidden() && !InventarioAccesorios.Contains(Accesorio))
		{
			AccesorioCercano = Accesorio;
		}
	}
}

void AJuegoIslaLlaveCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor == AccesorioCercano)
	{
		AccesorioCercano = nullptr;
	}
}

void AJuegoIslaLlaveCharacter::RecogerAccesorio()
{
	if (AccesorioCercano != nullptr)
	{
		InventarioAccesorios.Add(AccesorioCercano);
		AccesorioCercano->SetActorHiddenInGame(true);
		AccesorioCercano->SetActorEnableCollision(false);
		AccesorioCercano = nullptr;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Accesorio guardado! En inventario: %d"), InventarioAccesorios.Num()));
		}
	}
}

void AJuegoIslaLlaveCharacter::SoltarAccesorio()
{
	if (InventarioAccesorios.Num() > 0)
	{
		AFMAccesorio* AccesorioASoltar = InventarioAccesorios.Pop();
		if (AccesorioASoltar != nullptr)
		{
			FVector PosicionSoltar = GetActorLocation() + (GetActorForwardVector() * 150.f);
			AccesorioASoltar->SetActorLocation(PosicionSoltar);
			AccesorioASoltar->SetActorHiddenInGame(false);
			AccesorioASoltar->SetActorEnableCollision(true);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Accesorio soltado! Quedan: %d"), InventarioAccesorios.Num()));
			}
		}
	}
}