// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/BatteryComponent.h"
#include "Public/TimerManager.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values for this component's properties
UBatteryComponent::UBatteryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBatteryComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupBatteryDrainingTimer();
	
	InitialMaxSpeed = GetMovementComponent()->MaxSpeed;
}

void UBatteryComponent::SetupBatteryDrainingTimer()
{
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("CostBatteryPercent"), BatteryDrainingAmount);

	GetWorld()->GetTimerManager().SetTimer(BatteryTimerHandle, TimerDel, BatteryDrainingPeriod, true);
}

void UBatteryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(BatteryTimerHandle);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


// Called every frame
void UBatteryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBatteryComponent::CostBatteryPercent(float DeltaPercent)
{

	if (CurrentPercent >= 50 && CurrentPercent - DeltaPercent < 50) 
	{
		OnBatteryDrained.Broadcast(0);
	}


	if (CurrentPercent >= 0 && CurrentPercent - DeltaPercent < 0) 
	{
		StartZeroBatteryMode();
		OnBatteryDrained.Broadcast(1);
	}

	CurrentPercent -= DeltaPercent;

	if (CurrentPercent <= -100) 
	{
		CurrentPercent = -100;
		OnBatteryDrained.Broadcast(2);
		// implement losing
	}
}

void UBatteryComponent::RecoverBatteryPercent(float DeltaPercent)
{
	if (CurrentPercent < 0)
	{
		RecoverMovement();
	}
	CurrentPercent += DeltaPercent;
	if (CurrentPercent > 100) { CurrentPercent = 100; }
}

UFloatingPawnMovement * UBatteryComponent::GetMovementComponent() const
{
	UActorComponent* MovementComponentObj = GetOwner()->GetComponentByClass(UFloatingPawnMovement::StaticClass());
	if (!MovementComponentObj) { return nullptr; }
	return Cast<UFloatingPawnMovement>(MovementComponentObj);
}

void UBatteryComponent::StartZeroBatteryMode()
{
	GetMovementComponent()->MaxSpeed = ZeroBatteryMovementSpeed;
}

void UBatteryComponent::RecoverMovement()
{
	GetMovementComponent()->MaxSpeed = InitialMaxSpeed;
}


