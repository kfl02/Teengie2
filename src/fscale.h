#pragma once

#ifndef TEENGIE2_FSCALE_H
#define TEENGIE2_FSCALE_H

const float fscale(const float originalMin,
                   const float originalMax,
                   const float newBegin,
                   const float newEnd,
                   const float inputValue,
                   float curve);

#endif // TEENGIE2_FSCALE_H