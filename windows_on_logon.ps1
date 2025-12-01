# should be executed as admin

$TaskName = "SSH_Tunnels"
$User = "user"
$ScriptPath = "C:\Users\user\on_boot.ps1"


# Remove old task if it exists
if (Get-ScheduledTask -TaskName $TaskName -ErrorAction SilentlyContinue) {
    Unregister-ScheduledTask -TaskName $TaskName -Confirm:$false
}

# Create trigger: run when the user logs in (Session 1)
$trigger = New-ScheduledTaskTrigger -AtLogon -User $User

# Start minimized, no window
$settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries `
                                          -DontStopIfGoingOnBatteries `
                                          -ExecutionTimeLimit 0

$action = New-ScheduledTaskAction -Execute "powershell.exe" `
    -Argument "-NoProfile -WindowStyle Hidden -File `"$ScriptPath`""

# Register the new task
Register-ScheduledTask -TaskName $TaskName `
                       -Action $action `
                       -Trigger $trigger `
                       -User $User `
                       -RunLevel Highest

Write-Host "Scheduled task '$TaskName' created successfully."
