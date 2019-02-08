// Fill out your copyright notice in the Description page of Project Settings.

#include "WinBox.h"
#include "Engine/TriggerVolume.h"

// Sets default values
AWinBox::AWinBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWinBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(WinBox)) { return; }

	if (WinBox->IsOverlappingActor(BlindPlayerActor)) 
	{
		//Show win screen
		UE_LOG(LogTemp, Warning, TEXT("peepeepoopoo hahahaa"))
	}
}

