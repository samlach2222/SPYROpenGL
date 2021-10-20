#include "IntermittentDuSpectacle.h"
#include <time.h>

const void IntermittentDuSpectacle::play_music()
{
  srand(time(NULL));
  int randNum = (rand() % 3) + 1;

  switch randNum
  {
    case 1 :
        PlaySound("music1", NULL, SND_FILENAME|SND_LOOP);
        break;
    case 2 :
        PlaySound("music2", NULL, SND_FILENAME|SND_LOOP);
        break;
    case 3 :
        PlaySound("music3", NULL, SND_FILENAME|SND_LOOP);
        break;

  }

}
