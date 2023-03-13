#pragma once

#ifndef TEENGIE2_FSCALE_H
#define TEENGIE2_FSCALE_H

float fscale(float originalMin,
                   float originalMax,
                   float newBegin,
                   float newEnd,
                   float inputValue,
                   float curve);

#endif // TEENGIE2_FSCALE_H