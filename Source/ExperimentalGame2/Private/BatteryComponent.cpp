// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/BatteryComponent.h"
#include "Public/TimerManager.h"

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
	
}

void UBatteryComponent::SetupBatteryDrainingTimer()
{
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("CostBatteryPercent"), BatteryDrainingPeriod);

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

void UBatteryComponent::CostBatteryPercent(float Percent)
{
	CurrentPercent -= Percent;
	if (CurrentPercent < 0) { CurrentPercent = 0; }
}

void UBatteryComponent::RecoverBatteryPercent(float DeltaPercent)
{
	CurrentPercent += DeltaPercent;
}

