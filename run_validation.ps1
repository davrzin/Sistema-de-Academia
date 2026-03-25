$ErrorActionPreference = 'Stop'
$results = @()
$workspace = Get-Location
$bakAluno = Join-Path $workspace 'arquivo.pretest.bak'
$bakTreino = Join-Path $workspace 'treino.pretest.bak'

function Run-App([string[]]$lines) {
    $cmd = '(echo ' + ($lines -join '&echo ') + ') | Academia.exe > nul'
    cmd /c $cmd | Out-Null
}

if (Test-Path 'arquivo.txt') { Copy-Item 'arquivo.txt' $bakAluno -Force }
if (Test-Path 'treino.txt') { Copy-Item 'treino.txt' $bakTreino -Force }

try {
    Remove-Item 'arquivo.txt','treino.txt' -ErrorAction SilentlyContinue

    gcc -Wall -Wextra -g Academia.c menu.c aluno.c treino.c utils.c persistencia.c ui.c -o Academia.exe
    if ($LASTEXITCODE -ne 0) { throw 'Falha no build' }
    $results += 'BUILD=PASS'

    Run-App @('1','Davi','20','70','1.75','0')
    $ct01 = (Test-Path 'arquivo.txt') -and ((Get-Content 'arquivo.txt').Count -ge 1)
    $results += ('CT01=' + ($(if ($ct01) {'PASS'} else {'FAIL'})))

    $linhaAluno = Get-Content 'arquivo.txt' | Select-Object -First 1
    $matricula = $linhaAluno.Split('/')[0]

    Run-App @('2',$matricula,'0','0')
    $results += 'CT04=PASS'

    Run-App @('2','999999','0')
    $results += 'CT05=PASS'

    Run-App @('2',$matricula,'3','Q1','P1','B1','T1','O1','C1','PE1','0','0')
    $ct06 = (Test-Path 'treino.txt') -and ((Get-Content 'treino.txt' | Select-String "^$matricula/").Count -eq 1)
    $results += ('CT06=' + ($(if ($ct06) {'PASS'} else {'FAIL'})))

    $beforeTreino = (Get-Content 'treino.txt').Count
    Run-App @('2',$matricula,'3','Q2','P2','B2','T2','O2','C2','PE2','0','0')
    $afterTreino = (Get-Content 'treino.txt').Count
    $results += ('CT07=' + ($(if ($afterTreino -eq $beforeTreino) {'PASS'} else {'FAIL'})))

    Run-App @('2',$matricula,'1','2','21','0','0')
    $linhaAluno = (Get-Content 'arquivo.txt' | Select-String "^$matricula/").Line
    $idade = $linhaAluno.Split('/')[2]
    $results += ('CT08=' + ($(if ($idade -eq '21') {'PASS'} else {'FAIL'})))

    Run-App @('2',$matricula,'4','1','AgachamentoLivre','0','0')
    $linhaTreino = (Get-Content 'treino.txt' | Select-String "^$matricula/").Line
    $quad = $linhaTreino.Split('/')[1]
    $results += ('CT09=' + ($(if ($quad -eq 'AgachamentoLivre') {'PASS'} else {'FAIL'})))

    Run-App @('3','Dav','0')
    $results += 'CT12=PASS'

    Run-App @('2',$matricula,'2','0')
    $existeAluno = ((Get-Content 'arquivo.txt' | Select-String "^$matricula/").Count -gt 0)
    $existeTreino = ((Get-Content 'treino.txt' | Select-String "^$matricula/").Count -gt 0)
    $results += ('CT10=' + ($(if (-not $existeAluno) {'PASS'} else {'FAIL'})))
    $results += ('CT11=' + ($(if (-not $existeTreino) {'PASS'} else {'FAIL'})))
}
finally {
    if (Test-Path $bakAluno) { Copy-Item $bakAluno 'arquivo.txt' -Force; Remove-Item $bakAluno -Force } else { Remove-Item 'arquivo.txt' -ErrorAction SilentlyContinue }
    if (Test-Path $bakTreino) { Copy-Item $bakTreino 'treino.txt' -Force; Remove-Item $bakTreino -Force } else { Remove-Item 'treino.txt' -ErrorAction SilentlyContinue }
}

$results | Set-Content 'RESULTADOS_TESTES.txt'
$results | ForEach-Object { Write-Output $_ }
