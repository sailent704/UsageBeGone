# UsageBeGone
UsageBeGone is a tool primarily targetted at anyone who's ever had problems with background programs randomly using too much CPU (like in the screenshot below).
![High CPU Usage](https://lh3.googleusercontent.com/5cn16ch46abTbRyZM-9s4jFqsJUiy3iCSIC8ckvBLIgG84lx8FeesuiS2G67KgqDZOgigYFlGHz8hvTKdg1WBq7LZPoLQX3RSpvJBhYkZHgDx4L5cOj0j8mPDgjEyJODPDMYsSluADskb93R1Rkz0Y_KulUUo-sZ04PkvXx9j6sNECg27ixZaXhdBs72515IsUzw2Bqe5EfqLSfC0y2iU5IeuXndMzIIcM2dyhJM9FNL-AMwJyq3q9jSGBY4w22yMgZXfbeG2Vo_UR2vByO5UnNeFIlG9cj8gKUrvy9JSR7lUwpL6_hm84YqRiTLqbe2Jj7iKudT5grcDrRWTs1WVU2fI0pg875XYEKCGMhW8jgWXp_MI_bSzOp_h6nLpnwNz1BIAiDZ6jMWfsNHC1g5W8jwZXjm-QssY9dR8ASJrhN6x65L7TaAEtZqEjrPmRzILcUsegZkY-jMYhcNPAUj3In_AuLDf4W8LRPdIkQmF0wMrocvFSadPo2HDHA8pN1CRxuXcMFfLsoSF1t0gtNOn8g67wcxmtxqK7VVu2A-PYwYxCFZp99Ta2uWO7Ee6AtQOuHhL5zA2wO08w14PB3aBAGOjnJlphkJCKy6c4Ku7yJajq685fds_0b4q8vsLdCPYlPja8tQSvQqZV_nwEc1PudNvvuUUyQIKgzkwOnDg0RUUwDtneCbs-6UxYRV=w1132-h81-no?authuser=0)


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
