#ifdef TEST
#include "unity.h"

#include "input.h"
 char envp[][200] = {"SHELL=/bin/bash",
	"SESSION_MANAGER=local/user42-VirtualBox:@/tmp/.ICE-unix/1223,unix/user42-VirtualBox:/tmp/.ICE-unix/1223",
	"QT_ACCESSIBILITY=1",
	"COLORTERM=truecolor",
	"XDG_CONFIG_DIRS=/etc/xdg/xdg-xubuntu:/etc/xdg:/etc/xdg",
	"XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0",
	"XDG_MENU_PREFIX=xfce-",
	"CLUTTER_BACKEND=x11",
	"LANGUAGE=en_US",
	"TERMINATOR_DBUS_PATH=/net/tenshu/Terminator2",
	"LC_ADDRESS=fr_FR.UTF-8",
	"LC_NAME=fr_FR.UTF-8",
	"SSH_AUTH_SOCK=/run/user/1000/keyring/ssh",
	"TERMINATOR_UUID=urn:uuid:42c44c21-2ee8-4e69-9d69-2ff3125472c5",
	"DESKTOP_SESSION=xubuntu",
	"LC_MONETARY=fr_FR.UTF-8",
	"SSH_AGENT_PID=1340",
	"XDG_SEAT=seat0",
	"PWD=/home/user42/cursus_42/minishell/valid/ceedling_unit_tests",
	"LOGNAME=user42",
	"XDG_SESSION_DESKTOP=xubuntu",
	"QT_QPA_PLATFORMTHEME=gtk2",
	"XDG_SESSION_TYPE=x11",
	"GPG_AGENT_INFO=/run/user/1000/gnupg/S.gpg-agent:0:1",
	"XAUTHORITY=/home/user42/.Xauthority",
	"XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/user42",
	"GDM_LANG=en_US",
	"HOME=/home/user42",
	"LC_PAPER=fr_FR.UTF-8",
	"LANG=en_US.UTF-8",
	"XDG_CURRENT_DESKTOP=XFCE",
	"VTE_VERSION=6003",
	"XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0",
	"TERMINATOR_DBUS_NAME=net.tenshu.Terminator21a9d5db22c73a993ff0b42f64b396873",
	"LESSCLOSE=/usr/bin/lesspipe %s %s",
	"XDG_SESSION_CLASS=user",
	"TERM=xterm-256color",
	"LC_IDENTIFICATION=fr_FR.UTF-8",
	"GTK_OVERLAY_SCROLLING=0",
	"LESSOPEN=| /usr/bin/lesspipe %s",
	"USER=user42",
	"DISPLAY=:0.0",
	"SHLVL=1",
	"LC_TELEPHONE=fr_FR.UTF-8",
	"LC_MEASUREMENT=fr_FR.UTF-8",
	"XDG_VTNR=7",
	"XDG_SESSION_ID=c1",
	"XDG_RUNTIME_DIR=/run/user/1000",
	"LC_TIME=fr_FR.UTF-8",
	"XDG_DATA_DIRS=/usr/share/xubuntu:/usr/share/xfce4:/usr/local/share:/usr/share:/var/lib/snapd/desktop:/usr/share",
	"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
	"GDMSESSION=xubuntu",
	"DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus",
	"LC_NUMERIC=fr_FR.UTF-8"};


void setUp(void)
{
}

void tearDown(void)
{
}



void ft_free_global(t_global *global)
{
	if (!global)
		return ;
	/* if (global->user_input) */
	/* 	free(global->user_input) */
	if (global->pipe_split_user_input)
		ft_free_2d_array((void **)global->pipe_split_user_input);
	if (global->pipes_array)
		ft_free_2d_array((void **)global->pipes_array);
	global->user_input = NULL;
	global->pipe_split_user_input = NULL;
	global->pipes_array = NULL;
}

void test_should_return_last_fd_input(void)
{

	t_global *global = ft_create_global_struct("< /home/user42/cursus_42/minishell/valid/ceedling_unit_tests/test/tmp.txt cat", (char **)envp);
	int fd_input = ft_return_fd_input(global, 0);
	TEST_ASSERT_TRUE(fd_input > 2);
	if(fd_input > 2)
		close(fd_input);
	ft_free_global(global);
}

void test_should_return_last_fd_output(void)
{

	t_global *global = ft_create_global_struct("echo hola > /home/user42/cursus_42/minishell/valid/ceedling_unit_tests/test/tmp.txt", (char **)envp);
	int fd_output = ft_return_fd_output(global, 0);
	TEST_ASSERT_TRUE(fd_output > 2);
	if(fd_output > 2)
		close(fd_output);
	ft_free_global(global);
}

#endif // TEST

