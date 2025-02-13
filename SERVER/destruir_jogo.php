<?php
// Define o cabeçalho de resposta como JSON:
header('Content-Type: application/json');

// Obtém os dados enviados pelo cliente:
$input = file_get_contents('php://input');
$dados = json_decode($input, true);

// Verifica se os dados foram enviados corretamente:
if (!is_array($dados) || !isset($dados['arquivo']) || !isset($dados['dados'])) {
    echo json_encode([
        'status' => 'erro',
        'mensagem' => 'Os dados enviados não são válidos.'
    ]);
    exit;
}

// Extrai os campos do JSON:
$nomeArquivo = $dados['arquivo'];
$conteudo = $dados['dados'];

// Grava os dados no arquivo:
if (file_put_contents($nomeArquivo, $conteudo) !== false) {
    echo json_encode([
        'status' => 'sucesso',
        'mensagem' => 'Arquivo salvo com sucesso.'
    ]);
} else {
    echo json_encode([
        'status' => 'erro',
        'mensagem' => 'Não foi possível salvar o arquivo.'
    ]);
}

// Verifica se o arquivo existe:
if (file_exists($nomeArquivo)) {
    // Tenta excluir o arquivo
    if (unlink($nomeArquivo)) {
        echo json_encode([
            'status' => 'sucesso',
            'mensagem' => 'Seção encerrada com sucesso.'
        ]);
    } else {
        echo json_encode([
            'status' => 'erro',
            'mensagem' => 'Erro ao encerrar seção.'
        ]);
    }
} else {
    echo json_encode([
        'status' => 'erro',
        'mensagem' => 'Seção inexistente.'
    ]);
}

// Remove arquivos .txt com mais de 40 minutos desde a última modificação:
$dir = __DIR__;
$tempoLimite = time() - (40 * 60);

foreach (glob("$dir/*.txt") as $arquivo) {
    if (filemtime($arquivo) < $tempoLimite) {
        unlink($arquivo);
    }
}
?>
