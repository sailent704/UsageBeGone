# Urgent Note
UsageBeGone is undergoing a massive rewrite. During this time, no updates are to be released. Expected release is on Friday the 4th, September 2020.

# UsageBeGone
UsageBeGone is a tool primarily targetted at anyone who's ever had problems with background programs randomly using too much CPU (like in the screenshot below).
![High CPU Usage](https://raw.githubusercontent.com/sailent704/UsageBeGone/master/highCPU.png)


It can keep track of an application's CPU usage and automatically suspend it, all without user interaction.
The application is currently in heavy development, so expect daily updates with new features.
This application is provided "as-is", and I am not responsible for any lost data.

# Configuration
In order for the application to monitor a process, fill out the ``processes.conf`` file by putting each process name (case insensitive) on a new line - like this:
```
Process1.exe
Process2.exe
Process3.exe
```
You may also visit ``settings.conf`` to change the CPU usage threshold and the process freeze time. 
Once more features are added, your configs may become outdated. To refresh them, simply delete the old ones and run the executable.

It will create new ones automatically. (Note: This also works if you messed up your config!)

The application is configured to display the loaded values at start-up, so if your settings don't match, try refreshing the config or reloading the application.
