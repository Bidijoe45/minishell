#include "fresh.h"

void	ft_play_music(t_fresh *fresh)
{
	fresh->music_pid = fork();
	if (!fresh->music_pid)
	{
		system("afplay ./resources/music.mp3");
		exit(0);
	}
}