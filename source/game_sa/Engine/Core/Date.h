/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CDate {
public:
    int32_t seconds;
    int32_t minutes;
    int32_t hours;
    int32_t day;
    int32_t month;
    int32_t year;

public:
    CDate();

    bool operator<(CDate const& rhs);
    bool operator==(CDate const& rhs);
    bool operator>(CDate const& rhs);

    void PopulateDateFields(const char& seconds, const char& minutes, const char& hours, const char& day, const char& month, short year);
};

VALIDATE_SIZE(CDate, 0x18);
