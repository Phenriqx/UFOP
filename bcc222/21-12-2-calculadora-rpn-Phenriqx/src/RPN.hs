module RPN where

import Text.Read (readMaybe)
import System.IO (hSetBuffering, stdout, BufferMode(NoBuffering))

-- | Avalia uma expressão em Notação Polonesa Reversa (RPN).
-- Retorna Just resultado em caso de sucesso, ou Nothing em caso de erro
-- (pilha insuficiente, operador desconhecido, divisão por zero, etc).
solveRPN :: String -> Maybe Double
solveRPN expression = processa [] (words expression)
  where
    -- | Função auxiliar recursiva que rastreia a pilha e consome os tokens.
    processa :: [Double] -> [String] -> Maybe Double

    -- Caso Base: Todos os tokens foram processados
    processa pilha [] = case pilha of
      [resultado] -> Just resultado  -- Sucesso: exatamente um elemento na pilha
      _           -> Nothing         -- Erro: pilha vazia ou com elementos isolados (sobra de operandos)

    -- Caso Recursivo: Ainda há tokens para processar
    processa pilha (token:tokensRestantes) = case token of
      "+" -> case pilha of
        (y:x:resto) -> processa ((x + y) : resto) tokensRestantes
        _           -> Nothing
      "-" -> case pilha of
        (y:x:resto) -> processa ((x - y) : resto) tokensRestantes
        _           -> Nothing
      "*" -> case pilha of
        (y:x:resto) -> processa ((x * y) : resto) tokensRestantes
        _           -> Nothing
      "/" -> case pilha of
        (y:x:resto) -> if y == 0
                         then Nothing -- Proteção explícita contra divisão por zero
                         else processa ((x / y) : resto) tokensRestantes
        _           -> Nothing

      -- Se não for operador, tenta tratar como um número literal Double
      numeroStr -> case readMaybe numeroStr of
        Just n  -> processa (n : pilha) tokensRestantes -- Empilha o número e continua
        Nothing -> Nothing                             -- Token inválido/desconhecido

-- | Ação principal: Lê entrada do usuário, avalia e imprime o resultado.
main :: IO ()
main = do
  hSetBuffering stdout NoBuffering
  putStrLn "Calculadora RPN Segura"
  loopREPL

-- | Laço de repetição interativo (REPL) da calculadora.
loopREPL :: IO ()
loopREPL = do
  putStr "> "
  entrada <- getLine
  -- Condição de parada: string vazia ou comando de saída literal
  if null entrada || entrada == "sair"
    then putStrLn "Fim."
    else do
      case solveRPN entrada of
        Just v  -> putStrLn $ "Resultado: " ++ show v
        Nothing -> putStrLn "Erro: Expressão inválida ou erro matemático."
      loopREPL
