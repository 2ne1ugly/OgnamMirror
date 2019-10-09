// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellSniperRifleRecoil.h"
#include "Camera/CameraAnimInst.h"
#include "Engine/Engine.h"
#include "Camera/PlayerCameraManager.h"

DECLARE_CYCLE_STAT(TEXT("CameraShakePlayShake"), STAT_PlayShake, STATGROUP_Game);

UMaxwellSniperRifleRecoil::UMaxwellSniperRifleRecoil()
{
	float Duration = .5f;


	RotOscillation.Pitch.Amplitude = 2.f;
	RotOscillation.Pitch.Frequency = PI;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	OscillationDuration = Duration;
	OscillationBlendInTime = .025f;
	OscillationBlendOutTime = .0f;
	FOVOscillation.Amplitude = 1.f;
	FOVOscillation.Frequency = PI;
	FOVOscillation.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
}

void UMaxwellSniperRifleRecoil::PlayShake(APlayerCameraManager* Camera, float Scale, ECameraAnimPlaySpace::Type InPlaySpace, FRotator UserPlaySpaceRot)
{
	SCOPE_CYCLE_COUNTER(STAT_PlayShake);

	ShakeScale = Scale;
	CameraOwner = Camera;

	// init oscillations
	if (OscillationDuration != 0.f)
	{

		if (OscillatorTimeRemaining > 0.f)
		{
			// this shake was already playing
			OscillatorTimeRemaining = OscillationDuration;

			if (bBlendingOut)
			{
				bBlendingOut = false;
				CurrentBlendOutTime = 0.f;

				// stop any blendout and reverse it to a blendin
				if (OscillationBlendInTime > 0.f)
				{
					bBlendingIn = true;
					CurrentBlendInTime = OscillationBlendInTime * (1.f - CurrentBlendOutTime / OscillationBlendOutTime);
				}
				else
				{
					bBlendingIn = false;
					CurrentBlendInTime = 0.f;
				}
			}
		}
		else
		{
			RotSinOffset.X = PI / 2.f;
			RotSinOffset.Y = FFOscillator::GetInitialOffset(RotOscillation.Yaw);
			RotSinOffset.Z = FFOscillator::GetInitialOffset(RotOscillation.Roll);

			LocSinOffset.X = FFOscillator::GetInitialOffset(LocOscillation.X);
			LocSinOffset.Y = FFOscillator::GetInitialOffset(LocOscillation.Y);
			LocSinOffset.Z = FFOscillator::GetInitialOffset(LocOscillation.Z);

			FOVSinOffset = 3 * PI / 2.f;

			InitialLocSinOffset = LocSinOffset;
			InitialRotSinOffset = RotSinOffset;
			InitialFOVSinOffset = FOVSinOffset;

			OscillatorTimeRemaining = OscillationDuration;

			if (OscillationBlendInTime > 0.f)
			{
				bBlendingIn = true;
				CurrentBlendInTime = 0.f;
			}
		}
	}

	// init cameraanim shakes
	if (Anim != nullptr)
	{
		if (AnimInst)
		{
			float const Duration = bRandomAnimSegment ? RandomAnimSegmentDuration : 0.f;
			float const FinalAnimScale = Scale * AnimScale;
			AnimInst->Update(AnimPlayRate, FinalAnimScale, AnimBlendInTime, AnimBlendOutTime, Duration);
		}
		else
		{
			bool bLoop = false;
			bool bRandomStart = false;
			float Duration = 0.f;
			if (bRandomAnimSegment)
			{
				bLoop = true;
				bRandomStart = true;
				Duration = RandomAnimSegmentDuration;
			}

			float const FinalAnimScale = Scale * AnimScale;
			if (FinalAnimScale > 0.f)
			{
				if (CameraOwner)
				{
					AnimInst = CameraOwner->PlayCameraAnim(Anim, AnimPlayRate, FinalAnimScale, AnimBlendInTime, AnimBlendOutTime, bLoop, bRandomStart, Duration, InPlaySpace, UserPlaySpaceRot);
				}
				else
				{
					// allocate our own instance and start it
					AnimInst = NewObject<UCameraAnimInst>(this);
					if (AnimInst)
					{
						// note: we don't have a temp camera actor necessary for evaluating a camera anim.
						// caller is responsible in this case for providing one by calling SetTempCameraAnimActor() on the shake instance before playing the shake
						AnimInst->Play(Anim, TempCameraActorForCameraAnims, AnimPlayRate, FinalAnimScale, AnimBlendInTime, AnimBlendOutTime, bLoop, bRandomStart, Duration);
						AnimInst->SetPlaySpace(InPlaySpace, UserPlaySpaceRot);
					}
				}
			}
		}
	}

	PlaySpace = InPlaySpace;
	if (InPlaySpace == ECameraAnimPlaySpace::UserDefined)
	{
		UserPlaySpaceMatrix = FRotationMatrix(UserPlaySpaceRot);
	}

	ReceivePlayShake(Scale);

}
