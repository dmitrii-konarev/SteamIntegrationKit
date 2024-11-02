// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_InputLibrary.h"

void USIK_InputLibrary::ActivateActionSet(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetHandle)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->ActivateActionSet(InputHandle.Result, ActionSetHandle.Result);
}

void USIK_InputLibrary::ActivateActionSetLayer(FSIK_InputHandle InputHandle,
	FSIK_InputActionSetHandle ActionSetLayerHandle)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->ActivateActionSetLayer(InputHandle.Result, ActionSetLayerHandle.Result);
}

void USIK_InputLibrary::DeactivateActionSetLayer(FSIK_InputHandle InputHandle,
	FSIK_InputActionSetHandle ActionSetLayerHandle)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->DeactivateActionSetLayer(InputHandle.Result, ActionSetLayerHandle.Result);
}

void USIK_InputLibrary::DeactivateAllActionSetLayers(FSIK_InputHandle InputHandle)
{
}

int64 USIK_InputLibrary::GetActiveActionSetLayers(FSIK_InputHandle InputHandle,	TArray<FSIK_InputActionSetHandle>& ActionSetHandles)
{
	if(!SteamInput())
	{
		return 0;
	}
	TArray<InputActionSetHandle_t> LocalHandle;
	LocalHandle.SetNum(STEAM_INPUT_MAX_ACTIVE_LAYERS);
	auto Result = SteamInput()->GetActiveActionSetLayers(InputHandle.Result, LocalHandle.GetData());
	for(auto Handle : LocalHandle)
	{
		ActionSetHandles.Add(Handle);
	}
	return Result;
}

FSIK_InputActionSetHandle USIK_InputLibrary::GetActionSetHandle(FString ActionSetName)
{
	if(!SteamInput())
	{
		return FSIK_InputActionSetHandle();
	}
	return FSIK_InputActionSetHandle(SteamInput()->GetActionSetHandle(TCHAR_TO_ANSI(*ActionSetName)));
}

FSIK_InputAnalogActionData USIK_InputLibrary::GetAnalogActionData(FSIK_InputHandle InputHandle,
	FSIK_InputAnalogActionHandle AnalogActionHandle)
{
	if(!SteamInput())
	{
		return FSIK_InputAnalogActionData();
	}
	return SteamInput()->GetAnalogActionData(InputHandle.Result, AnalogActionHandle.Result);
}

FSIK_InputAnalogActionHandle USIK_InputLibrary::GetAnalogActionHandle(FString AnalogActionName)
{
	if(!SteamInput())
	{
		return FSIK_InputAnalogActionHandle();
	}
	return FSIK_InputAnalogActionHandle(SteamInput()->GetAnalogActionHandle(TCHAR_TO_ANSI(*AnalogActionName)));
}

int64 USIK_InputLibrary::GetAnalogActionOrigins(FSIK_InputHandle InputHandle, FSIK_InputActionSetHandle ActionSetHandle,
	FSIK_InputAnalogActionHandle AnalogActionHandle, TArray<TEnumAsByte<ESIK_InputActionOrigin>>& OriginsOut)
{
	if(!SteamInput())
	{
		return 0;
	}
	TArray<EInputActionOrigin> LocalOrigins;
	LocalOrigins.SetNum(STEAM_INPUT_MAX_ORIGINS);
	auto Result = SteamInput()->GetAnalogActionOrigins(InputHandle.Result, ActionSetHandle.Result, AnalogActionHandle.Result, LocalOrigins.GetData());
	for(auto Origin : LocalOrigins)
	{
		OriginsOut.Add(static_cast<ESIK_InputActionOrigin>(Origin));
	}
	return Result;
}

int64 USIK_InputLibrary::GetConnectedControllers(TArray<FSIK_InputHandle>& HandlesOut)
{
	if(!SteamInput())
	{
		return 0;
	}
	TArray<InputHandle_t> LocalHandles;
	LocalHandles.SetNum(STEAM_INPUT_MAX_COUNT);
	auto Result = SteamInput()->GetConnectedControllers(LocalHandles.GetData());
	for(auto Handle : LocalHandles)
	{
		HandlesOut.Add(Handle);
	}
	return Result;
}

FSIK_InputHandle USIK_InputLibrary::GetControllerForGamepadIndex(int32 Index)
{
	if(!SteamInput())
	{
		return FSIK_InputHandle();
	}
	return SteamInput()->GetControllerForGamepadIndex(Index);
}

FSIK_InputActionSetHandle USIK_InputLibrary::GetCurrentActionSet(FSIK_InputHandle InputHandle)
{
	if(!SteamInput())
	{
		return FSIK_InputActionSetHandle();
	}
	return FSIK_InputActionSetHandle(SteamInput()->GetCurrentActionSet(InputHandle.Result));
}

FSIK_InputDigitalActionData USIK_InputLibrary::GetDigitalActionData(FSIK_InputHandle InputHandle,
                                                                    FSIK_InputDigitalActionHandle DigitalActionHandle)
{
	if(!SteamInput())
	{
		return FSIK_InputDigitalActionData();
	}
	return SteamInput()->GetDigitalActionData(InputHandle.Result, DigitalActionHandle.Result);
}

FSIK_InputDigitalActionHandle USIK_InputLibrary::GetDigitalActionHandle(FString DigitalActionName)
{
	if(!SteamInput())
	{
		return FSIK_InputDigitalActionHandle();
	}
	return SteamInput()->GetDigitalActionHandle(TCHAR_TO_ANSI(*DigitalActionName));
}

int64 USIK_InputLibrary::GetGamepadIndexForController(FSIK_InputHandle InputHandle)
{
	if(!SteamInput())
	{
		return 0;
	}
	return SteamInput()->GetGamepadIndexForController(InputHandle.Result);
}

FString USIK_InputLibrary::GetGlyphForActionOrigin(TEnumAsByte<ESIK_InputActionOrigin> Origin)
{
	if(!SteamInput())
	{
		return FString();
	}
	return TCHAR_TO_UTF8(SteamInput()->GetGlyphForActionOrigin_Legacy(static_cast<EInputActionOrigin>(Origin.GetValue())));
}

ESIK_SteamInputType USIK_InputLibrary::GetInputTypeForHandle(FSIK_InputHandle InputHandle)
{
	if(!SteamInput())
	{
		return ESIK_SteamInputType::ESIK_SteamInputType_Unknown;
	}
	return static_cast<ESIK_SteamInputType>(SteamInput()->GetInputTypeForHandle(InputHandle.Result));
}

FSIK_InputMotionData USIK_InputLibrary::GetMotionData(FSIK_InputHandle InputHandle)
{
	if(!SteamInput())
	{
		return FSIK_InputMotionData();
	}
	return SteamInput()->GetMotionData(InputHandle.Result);
}

FString USIK_InputLibrary::GetStringForActionOrigin(TEnumAsByte<ESIK_InputActionOrigin> Origin)
{
	if(!SteamInput())
	{
		return FString();
	}
	return SteamInput()->GetStringForActionOrigin(static_cast<EInputActionOrigin>(Origin.GetValue()));
}

bool USIK_InputLibrary::Init(bool bExplicitlyCallRunFrame)
{
	if(!SteamInput())
	{
		return false;
	}
	return SteamInput()->Init(bExplicitlyCallRunFrame);
}

void USIK_InputLibrary::RunFrame()
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->RunFrame();
}

void USIK_InputLibrary::SetDualSenseTriggerEffect(FSIK_InputHandle InputHandle, FSIK_ScePadTriggerEffectCommand L2,
	FSIK_ScePadTriggerEffectCommand R2)
{
	if(!SteamInput())
	{
		return;
	}
	ScePadTriggerEffectParam LocalParam;
	LocalParam.command[SCE_PAD_TRIGGER_EFFECT_PARAM_INDEX_FOR_R2] = R2.ToStruct();
	LocalParam.command[SCE_PAD_TRIGGER_EFFECT_PARAM_INDEX_FOR_L2] = L2.ToStruct();
	SteamInput()->SetDualSenseTriggerEffect(InputHandle.Result, &LocalParam);
}

void USIK_InputLibrary::SetLEDColor(FSIK_InputHandle InputHandle, FLinearColor Color,
	TEnumAsByte<ESIK_SteamControllerLEDFlag> LEDFlag)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->SetLEDColor(InputHandle.Result, Color.R, Color.G, Color.B, static_cast<ESteamControllerLEDFlag>(LEDFlag.GetValue()));
}

bool USIK_InputLibrary::ShowBindingPanel(FSIK_InputHandle InputHandle)
{
	if(!SteamInput())
	{
		return false;
	}
	return SteamInput()->ShowBindingPanel(InputHandle.Result);
}

bool USIK_InputLibrary::Shutdown()
{
	if(!SteamInput())
	{
		return false;
	}
	return SteamInput()->Shutdown();
}

void USIK_InputLibrary::StopAnalogActionMomentum(FSIK_InputHandle InputHandle,
	FSIK_InputAnalogActionHandle AnalogActionHandle)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->StopAnalogActionMomentum(InputHandle.Result, AnalogActionHandle.Result);
}

void USIK_InputLibrary::TriggerHapticPulse(FSIK_InputHandle InputHandle, TEnumAsByte<ESIK_SteamControllerPad> TargetPad,
	uint8 DurationMicroSec)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->Legacy_TriggerHapticPulse(InputHandle.Result, static_cast<ESteamControllerPad>(TargetPad.GetValue()), DurationMicroSec);
}

void USIK_InputLibrary::TriggerRepeatedHapticPulse(FSIK_InputHandle InputHandle,
	TEnumAsByte<ESIK_SteamControllerPad> TargetPad, uint8 DurationMicroSec, uint8 OffMicroSec, uint8 Repeat,
	uint8 Flags)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->Legacy_TriggerRepeatedHapticPulse(InputHandle.Result, static_cast<ESteamControllerPad>(TargetPad.GetValue()), DurationMicroSec, OffMicroSec, Repeat, Flags);
}

void USIK_InputLibrary::TriggerVibration(FSIK_InputHandle InputHandle, uint8 LeftSpeed, uint8 RightSpeed)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->TriggerVibration(InputHandle.Result, LeftSpeed, RightSpeed);
}

void USIK_InputLibrary::TriggerVibrationExtended(FSIK_InputHandle InputHandle, uint8 LeftSpeed, uint8 RightSpeed,
	uint8 LeftTriggerSpeed, uint8 RightTriggerSpeed)
{
	if(!SteamInput())
	{
		return;
	}
	SteamInput()->TriggerVibrationExtended(InputHandle.Result, LeftSpeed, RightSpeed, LeftTriggerSpeed, RightTriggerSpeed);
}

TEnumAsByte<ESIK_InputActionOrigin> USIK_InputLibrary::GetActionOriginFromXboxOrigin(FSIK_InputHandle InputHandle,
	TEnumAsByte<ESIK_XboxOrigin> XboxOrigin)
{
	if(!SteamInput())
	{
		return ESIK_InputActionOrigin::ESIK_InputActionOrigin_None;
	}
	return static_cast<ESIK_InputActionOrigin>(SteamInput()->GetActionOriginFromXboxOrigin(InputHandle.Result, static_cast<EXboxOrigin>(XboxOrigin.GetValue())));
}

bool USIK_InputLibrary::GetDeviceBindingRevision(FSIK_InputHandle InputHandle, int32& Major, int32& Minor)
{
	if(!SteamInput())
	{
		return false;
	}
	int LocalMajor;
	int LocalMinor;
	auto Result = SteamInput()->GetDeviceBindingRevision(InputHandle.Result, &LocalMajor, &LocalMinor);
	Major = LocalMajor;
	Minor = LocalMinor;
	return Result;
}

int64 USIK_InputLibrary::GetRemotePlaySessionID(FSIK_InputHandle InputHandle)
{
	if(!SteamInput())
	{
		return 0;
	}
	return SteamInput()->GetRemotePlaySessionID(InputHandle.Result);
}

TEnumAsByte<ESIK_InputActionOrigin> USIK_InputLibrary::TranslateActionOrigin(TEnumAsByte<ESIK_SteamInputType> eDestinationInputType, TEnumAsByte<ESIK_InputActionOrigin> eSourceActionOrigin)
{
	if(!SteamInput())
	{
		return ESIK_InputActionOrigin::ESIK_InputActionOrigin_None;
	}
	return static_cast<ESIK_InputActionOrigin>(SteamInput()->TranslateActionOrigin(static_cast<ESteamInputType>(eDestinationInputType.GetValue()), static_cast<EInputActionOrigin>(eSourceActionOrigin.GetValue())));
}

int64 USIK_InputLibrary::GetDigitalActionOrigins(FSIK_InputHandle InputHandle,
                                                 FSIK_InputActionSetHandle ActionSetHandle, FSIK_InputDigitalActionHandle DigitalActionHandle,
                                                 TArray<TEnumAsByte<ESIK_InputActionOrigin>>& OriginsOut)
{
	if(!SteamInput())
	{
		return 0;
	}
	TArray<EInputActionOrigin> LocalOrigins;
	LocalOrigins.SetNum(STEAM_INPUT_MAX_ORIGINS);
	auto Result = SteamInput()->GetDigitalActionOrigins(InputHandle.Result, ActionSetHandle.Result, DigitalActionHandle.Result, LocalOrigins.GetData());
	for(auto Origin : LocalOrigins)
	{
		OriginsOut.Add(static_cast<ESIK_InputActionOrigin>(Origin));
	}
	return Result;
}
