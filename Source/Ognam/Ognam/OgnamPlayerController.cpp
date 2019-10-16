	// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerController.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystemTypes.h"
#include "GameFramework/PlayerState.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "Blueprint/UserWidget.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "OgnamCharacter.h"
#include "Engine/World.h"
#include "DamageText.h"
#include "OgnamPlayerstate.h"
#include "Sound/SoundCue.h"
#include "Ognam/OgnamMacro.h"
#include "Materials/MaterialInstanceDynamic.h"

AOgnamPlayerController::AOgnamPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/OgnamHUD"));
	if (HUDFinder.Succeeded())
	{
		OgnamHUDClass = HUDFinder.Class;
	}
	else
	{
		O_LOG(TEXT("Not Loaded"));
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MenuHUDFinder(TEXT("/Game/UI/GameMenu"));
	if (MenuHUDFinder.Succeeded())
	{
		MenuHUDClass = MenuHUDFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameInfoHUDFinder(TEXT("/Game/UI/GameInfo/GameInfo"));
	if (GameInfoHUDFinder.Succeeded())
	{
		GameInfoHUDClass = GameInfoHUDFinder.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> HitSoundCue(TEXT("SoundCue'/Game/Sounds/General/hitsound_Cue.hitsound_Cue'"));
	HitSound = HitSoundCue.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> KillSoundCue(TEXT("SoundCue'/Game/Sounds/General/Kill/ownage_Cue.ownage_Cue'"));
	KillSound = KillSoundCue.Object;

	LoadConfig();
}

void AOgnamPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MenuHUDClass && IsLocalPlayerController())
	{
		MenuHUD = CreateWidget<UUserWidget>(this, MenuHUDClass);
		MenuHUD->bIsFocusable = true;
	}
	if (GameInfoHUDClass && IsLocalPlayerController())
	{
		GameInfoHUD = CreateWidget<UUserWidget>(this, GameInfoHUDClass);
	}
}

void AOgnamPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOgnamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GameMenu"), EInputEvent::IE_Pressed, this, &AOgnamPlayerController::ShowMenu);
	InputComponent->BindAction(TEXT("GameInfo"), EInputEvent::IE_Pressed, this, &AOgnamPlayerController::ShowGameInfo);
	InputComponent->BindAction(TEXT("GameInfo"), EInputEvent::IE_Released, this, &AOgnamPlayerController::HideGameInfo);
}

void AOgnamPlayerController::ClientFeedbackDamageDealt_Implementation(AActor* Causer, AActor* Reciever, FVector Location, float Damage)
{
	if (Causer == Reciever)
	{
		return;
	}
	ADamageText* Text = GetWorld()->SpawnActor<ADamageText>(Location, FRotator::ZeroRotator);
	Text->SetDamage(Damage);
	ClientPlaySound(HitSound, 1.f, 1.f);
}

void AOgnamPlayerController::ClientFeedbackDamageRecieved_Implementation(AActor* Causer, AActor* Reciever, FVector Location, float Damage)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(Reciever);
	if (Character)
	{
		GetWorld()->GetTimerManager().SetTimer(Character->DamageTimer, 3.f, false);
	}
}

void AOgnamPlayerController::ClientGameStarted_Implementation()
{
	if (OgnamHUDClass && IsLocalPlayerController())
	{
		OgnamHUD = CreateWidget<UUserWidget>(this, OgnamHUDClass);

		//This part should be chosen properly
		if (OgnamHUD)
		{
			OgnamHUD->AddToViewport();
		}
	}
}

void AOgnamPlayerController::ClientRestart_Implementation(APawn* aPawn)
{
	Super::ClientRestart_Implementation(aPawn);

	AOgnamPlayerState* State = GetPlayerState<AOgnamPlayerState>();

	AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(aPawn);

	if (OgnamCharacter == nullptr)
	{
		return;
	}
	if (CharacterHUD && CharacterHUD->IsInViewport())
	{
		CharacterHUD->RemoveFromViewport();
		CharacterHUD = nullptr;
	}
	if (OgnamCharacter->CharacterSpecificHUDClass)
	{
		CharacterHUD = CreateWidget<UUserWidget>(this, OgnamCharacter->CharacterSpecificHUDClass);
		if (CharacterHUD)
		{
			CharacterHUD->AddToViewport();
		}
	}

}

void AOgnamPlayerController::ClientFeedbackKill_Implementation(AActor* Causer, AActor* Reciever)
{
	ClientPlaySound(KillSound, 10.f, 1.f);
}

void AOgnamPlayerController::ClientFeedbackDeath_Implementation(AActor* Causer, AActor* Reciever)
{
}

void AOgnamPlayerController::ShowMenu()
{
	if (!MenuHUD)
	{
		O_LOG_E(TEXT("No Menu"));
		return;
	}

	if (MenuHUD->IsInViewport())
	{
		MenuHUD->RemoveFromViewport();
		if (GetPawn())
		{
			GetPawn()->EnableInput(this);
		}
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		MenuHUD->AddToViewport();
		if (GetPawn())
		{
			GetPawn()->DisableInput(this);
		}
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
}

void AOgnamPlayerController::ShowGameInfo()
{
	if (!GameInfoHUD)
	{
		O_LOG_E(TEXT("No Game Info"));
		return;
	}

	GameInfoHUD->AddToViewport();
}

void AOgnamPlayerController::HideGameInfo()
{
	if (!GameInfoHUD)
	{
		O_LOG_E(TEXT("No Game Info"));
		return;
	}

	GameInfoHUD->RemoveFromViewport();
}

float AOgnamPlayerController::GetSensitivity() const
{
	return InputYawScale;
}

void AOgnamPlayerController::SetSensitivity(float Sens)
{
	InputPitchScale = -Sens;
	InputYawScale = Sens;
	SaveConfig();
}

void AOgnamPlayerController::JoinGame(FString Address)
{
	ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void AOgnamPlayerController::CreateGame(FString MapName)
{
	UGameplayStatics::OpenLevel(GetWorld(), *MapName, true, FString("?listen?numplayers=4"));
}

void AOgnamPlayerController::WhoAmI()
{
	IOnlineSubsystem* Sub = IOnlineSubsystem::Get();
	O_LOG(TEXT("Sub : %s"), *Sub->GetOnlineServiceName().ToString());
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	O_LOG(TEXT("Playerid : %s"), *LocalPlayer->GetPreferredUniqueNetId().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("My name is %s"), *PlayerState->GetPlayerName()));
}

void AOgnamPlayerController::SendMessage(FString& Message)
{
	AOgnamPlayerState* OgnamPlayerState = GetPlayerState<AOgnamPlayerState>();
	OgnamPlayerState->ServerSendMessage(Message);
	OgnamPlayerState->DisplayMessage(Message, OgnamPlayerState);
}
