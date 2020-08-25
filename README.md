# UsageBeGone
UsageBeGone is a tool primarily targetted at anyone who's ever had problems with background programs randomly using too much CPU (like in the screenshot below).
![High CPU Usage](https://lh3.googleusercontent.com/VG11Z6FQqvYCFXHH1NMYqWz5c7T5x8tG2WmKTuqT62_89FeaY5iJ6JO5jSWIre6Scpk685DkBLODITOTh4oR2YGKquWNOikafvzE257de4AiORUCZ7n_fwzL7WOsGS7JY_Z3TAWBspJCjC6X5ryRMz3mTi7znb2dFRKhoS3NW4V87Kubq1ompkdtbHsvNIzm2HtqJS0SbI_rZzJtpohquXQNW5DbtRAcDZwPn6lrAmTJZG6lSL6CnNsq3gkUihh0zgA2bmHBvSQoZQLual9_VBdmn5tu39B24IYLycl4MuEFgzTD9RsdpppKwKnVyqp10WeVqiP-onoWpFNh-wVEg8fQoALw7W-3F5edoh8n5qbd3QqbklJn8hq_i1TRzF2-Gl7lsvbu2UsKwcsmdP-7Dsr5F0fpvmYWlT9OyiKeUw8NPdHBk77Br1XaqR1qo_ptmGOBp17J3kuVfTjzTDhtiRFJ1llpSHxcx1tXybEmeKLZMp_TdpgOd_aWmAPeGezZR5BT5GYQzit3gfemNWVvU8brMDGA_1Y8iINjoMN3m0uNRTJV3zN0K_MZN4aVYyN7cWxdrr6Z_5WqL9xfmwBnWKkD5bz4t_xD2RbdPuCEfVRj59dxDHR8y5Uw2CuVeAIDaGFK1ajA0k8QUDCo5k_TE3FWvOiSs1NlMh2x7mz71B4fcBSxZ3qgHePh84cl=w1132-h81-no?authuser=0)


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
