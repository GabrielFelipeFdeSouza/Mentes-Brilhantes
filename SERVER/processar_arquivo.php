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
