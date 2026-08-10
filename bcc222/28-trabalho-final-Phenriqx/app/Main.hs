module Main where

import System.Environment (getArgs)
import System.IO (writeFile)
import System.Exit (exitFailure)

import TextAnalysis.Normalize (normalizeText)
import TextAnalysis.Statistics (basicStats)
import TextAnalysis.Frequency (countFrequencies, rankFrequencies, topFrequencies, filterStopwords)
import TextAnalysis.Report (buildReport, exportCSV)

data Options = Options
  { filePath        :: FilePath
  , topN            :: Int
  , ignoreStopwords :: Bool
  , outputFile      :: Maybe FilePath
  }

defaultOptions :: Options
defaultOptions = Options
  { filePath        = ""
  , topN            = 10
  , ignoreStopwords = False
  , outputFile      = Nothing
  }

parseArgs :: [String] -> Options -> Options
parseArgs [] opts = opts
parseArgs ("--top":n:rest) opts = parseArgs rest opts { topN = read n }
parseArgs ("--ignore-stopwords":rest) opts = parseArgs rest opts { ignoreStopwords = True }
parseArgs ("--output":out:rest) opts = parseArgs rest opts { outputFile = Just out }
parseArgs (file:rest) opts
  | null (filePath opts) = parseArgs rest opts { filePath = file }
  | otherwise            = parseArgs rest opts

main :: IO ()
main = do
  args <- getArgs
  if null args
    then putStrLn "Uso: cabal run analisador-texto -- <arquivo> [--top N] [--ignore-stopwords] [--output arquivo.csv]" >> exitFailure
    else do
      let opts = parseArgs args defaultOptions
      if null (filePath opts)
        then putStrLn "Erro: Caminho do arquivo não fornecido." >> exitFailure
        else do
          content <- readFile (filePath opts)
          let stats = basicStats content
              rawWords = normalizeText content
              processedWords = if ignoreStopwords opts then filterStopwords rawWords else rawWords
              freqTable = topFrequencies (topN opts) (rankFrequencies (countFrequencies processedWords))
              reportStr = buildReport stats freqTable

          putStr reportStr

          case outputFile opts of
            Just outPath -> do
              writeFile outPath (exportCSV freqTable)
              putStrLn $ "\n[Sucesso] Relatório CSV exportado para: " ++ outPath
            Nothing -> return ()