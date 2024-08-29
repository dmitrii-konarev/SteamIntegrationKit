// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SIK_SoundWaveProcedural.h"

void USIK_SoundWaveProcedural::SIK_QueueAudio(const TArray<uint8>& AudioData)
{
	QueueAudio(AudioData.GetData(), AudioData.Num());
}