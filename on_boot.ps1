Start-Process `
    -FilePath "PowerShell.exe" `
    -ArgumentList "-NoProfile", "-File", (Join-Path $HOME "on_boot_ssh_get_25880_on_0000.ps1") `
    -WindowStyle Hidden
Start-Process `
    -FilePath "PowerShell.exe" `
    -ArgumentList "-NoProfile", "-File", (Join-Path $HOME "on_boot_ssh_put_5900.ps1") `
    -WindowStyle Hidden
Start-Process `
    -FilePath "PowerShell.exe" `
    -ArgumentList "-NoProfile", "-File", (Join-Path $HOME "on_boot_ssh_put_22.ps1") `
    -WindowStyle Hidden
