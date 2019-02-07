// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Drone.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAudioListenerLocation();

}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADrone::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADrone::MoveRight);
	PlayerInputComponent->BindAxis("Ascent", this, &ADrone::Ascent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADrone::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADrone::LookUpAtRate);

}

void ADrone::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADrone::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ADrone::Ascent(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FVector Direction = GetActorUpVector();
		AddMovementInput(Direction, Value*AscentSpeedMod);
	}
}

void ADrone::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void ADrone::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADrone::UpdateAudioListenerLocation()
{
	if (!Controller) { return; }
	APlayerController* MyPlayerController = Cast<APlayerController>(Controller);
	if (!MyPlayerController) { return; }
	ACharacter* OtherPlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
	if (!OtherPlayerCharacter) { return; }
	USceneComponent* OtherPlayerEarComponent = OtherPlayerCharacter->GetComponentsByTag("Ear")[0]
	MyPlayerController->SetAudioListenerOverride(OtherPlayerCharacter->GetRootComponent(), FVector::ZeroVector, FRotator::ZeroRotator);
	//FVector AudioLocation, FrontDir, RightDir;
	//MyPlayerController->GetAudioListenerPosition(AudioLocation, FrontDir, RightDir);
	//UE_LOG(LogTemp, Warning, TEXT("AudioListenerLocation: %s"), *AudioLocation.ToString());
}


