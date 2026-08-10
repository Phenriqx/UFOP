module LogProcessor
  ( LogEntry,
    parseLog,
    filterErrors,
    countLogType,
    main
  )
where

-- Sinônimo de tipo para tornar as assinaturas mais legíveis
-- Representa: (Tipo, Data, Mensagem)
type LogEntry = (String, String, String)

-- | Converte uma linha crua de log em uma entrada estruturada.
-- Use 'words' para separar as palavras e casamento de padrão para extrair os campos.
parseLog :: String -> LogEntry
parseLog line = case words line of
  (tipo : dataStr : restoMsg) -> (tipo, dataStr, unwords restoMsg)
  _                           -> ("UNKNOWN", "", line)

-- | Retorna apenas as mensagens dos logs do tipo "ERROR".
-- Deve ser implementada usando recursão explícita.
filterErrors :: [LogEntry] -> [String]
filterErrors [] = []
filterErrors ((tipo, _, msg) : xs)
  | tipo == "ERROR" = msg : filterErrors xs
  | otherwise       = filterErrors xs

-- | Conta quantos logs de um determinado tipo existem na lista.
-- Deve ser implementada usando recursão explícita.
countLogType :: String -> [LogEntry] -> Int
countLogType _ [] = 0
countLogType targetType ((tipo, _, _) : xs)
  | tipo == targetType = 1 + countLogType targetType xs
  | otherwise          = countLogType targetType xs

parseAllLogs :: [String] -> [LogEntry]
parseAllLogs []       = []
parseAllLogs (l : ls) = parseLog l : parseAllLogs ls

-- | Função principal
main :: IO ()
main = do
  -- Lê todo o conteúdo da entrada padrão
  content <- getContents

  -- Divide o conteúdo por quebras de linha
  let rawLines = lines content
      -- Transforma todas as linhas cruas em LogEntry de forma recursiva
      entries  = parseAllLogs rawLines
      -- Filtra os erros e conta a quantidade do tipo "ERROR"
      errorMsgs = filterErrors entries
      totalErrors = countLogType "ERROR" entries

  -- Exibe os resultados formatados
  putStrLn $ "Total de erros encontrados: " ++ show totalErrors
  putStrLn "Mensagens de erro:"
  putStr (unlines errorMsgs)
