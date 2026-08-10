module Exercicios where

-- Definições de tipo para o Exercício 3
type Venda = (String, Double)
type Aluno = (String, Double, Double) -- nome, nota1, nota2

--
-- Exercício 1: refatorando para expressões lambda
--

-- Função original 1.1
somaQuadradosPares :: [Int] -> Int
somaQuadradosPares xs = sum (map f (filter g xs))
  where
    f x = x * x
    g x = even x

-- Sua implementação com lambdas:
somaQuadradosParesLambda :: [Int] -> Int
somaQuadradosParesLambda xs = sum (map (\x -> x * x) (filter (\x -> even x) xs))

-- Função original 1.2
stringsMaioresQue5 :: [String] -> [String]
stringsMaioresQue5 xs = filter g xs
  where
    g s = length s > 5

-- Sua implementação com lambdas:
stringsMaioresQue5Lambda :: [String] -> [String]
stringsMaioresQue5Lambda xs = filter (\s -> length s > 5) xs

-- Função original 1.3
adicionaExclamacaoPar :: [String] -> [String]
adicionaExclamacaoPar xs = map f (filter g xs)
  where
    f s = s ++ "!"
    g s = even (length s)

-- Sua implementação com lambdas:
adicionaExclamacaoParLambda :: [String] -> [String]
adicionaExclamacaoParLambda xs = map (\s -> s ++ "!") (filter (\s -> even (length s)) xs)

--
-- Exercício 2: funções especializadas com aplicação parcial e seções
--

-- Deve retornar True se um caractere for uma vogal minúscula.
ehVogal :: Char -> Bool
ehVogal = (`elem` "aeiou")

-- Deve adicionar o sufixo ".com" a uma string.
adicionaCom :: String -> String
adicionaCom = (++ ".com")

-- Deve retornar a diferença entre 10 e o argumento recebido.
subtraiDe10 :: Int -> Int
subtraiDe10 = (10 -)

--
-- Exercício 3: processamento de dados com lambdas e padrões
--

-- Aplica uma taxa de 10% apenas nos itens cujo preço seja maior que R$ 50,00.
aplicaTaxa :: [Venda] -> [Venda]
aplicaTaxa xs = map (\(nome, preco) -> if preco > 50.0 then (nome, preco * 1.1) else (nome, preco)) xs

-- Retorna uma lista de nomes dos alunos aprovados (média das notas >= 7.0).
alunosAprovados :: [Aluno] -> [String]
alunosAprovados xs = map (\(nome, _, _) -> nome) (filter (\(_, n1, n2) -> (n1 + n2) / 2 >= 7.0) xs)

-- Retorna o nome do produto e o preço final após aplicar um desconto de 5%.
aplicaDesconto :: [Venda] -> [(String, Double)]
aplicaDesconto xs = map (\(nome, preco) -> (nome, preco * 0.95)) xs

-- Ação principal para testes manuais.
main :: IO ()
main = do
  putStrLn "Use cabal test all para executar a suíte de testes."
  putStrLn "Edite src/Exercicios.hs para implementar as funções da atividade."
