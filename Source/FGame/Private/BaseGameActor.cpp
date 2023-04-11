// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameActor.h"
#include <Engine/Engine.h>

DEFINE_LOG_CATEGORY_STATIC(LogFGame, All, All);

// Sets default values
ABaseGameActor::ABaseGameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base mesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGameActor::BeginPlay()
{
	InitialLocation = GetActorLocation();

	Super::BeginPlay();

	//PrintTypes();
	//PrintStringTypes();
	//PrintTransform();
}

// Called every frame
void ABaseGameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ABaseGameActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
		case EMovementType::Sin:
		{
			FVector CurrentLocation = GetActorLocation();
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			SetActorLocation(CurrentLocation);
		}
		break;

		case EMovementType::Static: break;
		default: break;
	}
}

void ABaseGameActor::PrintTypes()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Warning, TEXT("IsDead: %i"), IsDead);
	UE_LOG(LogTemp, Warning, TEXT("HasWeapon: %i"), static_cast<int>(HasWeapon));
}

void ABaseGameActor::PrintStringTypes()
{
	FString Name = "John Connor";
	UE_LOG(LogFGame, Display, TEXT("Name: %s"), *Name);

	FString WeaponsNumStr = "Weapons num: " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health: " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "IsDead: " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n -- All stat -- \n %s \n %s \n %s \n "), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogFGame, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Stat, true, FVector2D(1.5f, 1.5f));
}

void ABaseGameActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogFGame, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogFGame, Warning, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(LogFGame, Warning, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogFGame, Warning, TEXT("Rotation: %s"), *Rotation.ToString());
	UE_LOG(LogFGame, Warning, TEXT("Scale: %s"), *Scale.ToString());

	UE_LOG(LogFGame, Error, TEXT("Transform: %s"), *Transform.ToHumanReadableString());
}

