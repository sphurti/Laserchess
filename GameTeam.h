#ifndef GAMETEAM_H
#define GAMETEAM_H
enum Team
{
    BLACK,
    WHITE,
    NO_TEAM,
};

#define OTHER_TEAM(x) x==BLACK? WHITE : BLACK

#endif
