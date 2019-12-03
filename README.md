
# K means - CPP

  

## DESCRIÇÃO

<p>Implementação do K means para clusterização de 4 bases de dados, utilizando a linguagem C++ e desenvolvido por: </p>

<ul>

<li>Gabriel Maximiniano - [GitHub](https://github.com/gabmaxs) [Twitter](https://twitter.com/gabmaxs_) </li>

</ul>

<p> Desenvolvido para a disciplina SIN 460 - Mineração de Dados do curso de Sistemas de Informação da UFV-CRP.</p>

  
  

## COMPILAR

<code> g++ kmeans.cpp -o kmeans </code>

  

## EXECUTAR

<p>Para executar o programa basta executar o seguinte comando: </p>

<code> ./kmeans -op *N* < *entrada* </code>

<p>

Onde *N* é a opção pré-definida de K. Para isso, temos os seguintes valores:

<ul>

<li>N = 1 -> K = 12</li>

<li>N = 2 -> K = 11</li>

<li>N = 3 -> K = 10</li>

<li>N = 4 -> K = 9</li>

</ul>

E a opção *entrada* é o arquivo de entrada da base de dados. Os arquivos pré-definos se encontram na pasta entradas e ja contém 4 arquivos. Para executar o código com algum desses arquivos, basta escolher dentre as opções:

<ul>

<li>entradas/base1.txt</li>

<li>entradas/base2.txt</li>

<li>entradas/base3.txt</li>

<li>entradas/base4.txt</li>

</ul>

Após execução do código, será gerado um 2 arquivos de saída, o primeiro no diretório ***saidas***, onde terá um arquivo de fácil entendimento. O segundo estará no diretório ***saidas_numeros***, e é o arquivo necessário para plotar visualmente o gráfico.

</p>

<p>

Além disso é possível alterar o nome do arquivo de saída, adicionando o argumento **-f**.

<code> ./kmeans -op 1 -f saida_base1.txt < entradas/base1.txt </code>

</p>

<p>

Ao adicionar o argumento **-v** é possível imprimir no console a saída do algoritmo.

</p>

<p>

Um exemplo completo para executar o código seria:

<code> ./kmeans -op 3 -f saida_base3.txt < entradas/base3.txt </code>

</p>

  

## FUNCIONAMENTO

  

<p>
 O código funciona da seguinte maneira:

 1. Leitura de dados: primeiro ele lê a entrada dos pontos dentro do arquivo de entrada, armazenando em um **vector** do tipo **point**;  
 2. Criação dos centroides: após a leitura de dados, a função **kmeans** é executada, onde é gerado de forma aleatória os K centroides;
 3. Classificação inicial: com os centroides definidos, os pontos são classificados para os centroides mais próximos;
 4. Movimentação de centroides: com todos os pontos já classificados, os centroides devem se mover, para isso é utilizado a média das distâncias entre ponto e centroide;
 5. Nova atribuição: após os centroides sendo re-calculados, é a vez dos pontos. Onde é visto para cada ponto se existe algum centroide mais próximo do que seu centroide atual.
 6. Repedir até não houver mudança: os passos 4 e 5 são repetidos até que os centroides não mudem mais, e com isso, temos os dados agrupados;
 7. Salvar resultado: após a finalização da função **kmeans**, o resultado é salvo no arquivo de saida.
</p>
<p>
Para medir a distância em 2 pontos foi utilizado a distância Euclidiana. E para escolher o valor de K para cada base, foi feito de forma empírica. Com isso, tem como valores recomendados de K: 
	<ul>
		<li>Base 1: K = 12</li>
		<li>Base 2: K = 11</li>
		<li>Base 3: K = 11</li>
		<li>Base 4: K = 10</li>
	</ul>
</p>

  ## VISUALIZAÇÃO DOS RESULTADOS
  
  <p>
	  Após a execução do algoritmo ele gera um arquivo de saída na pasta **saidas_numeros**, com ele é possível plotar os dados, a fim de verificar os mesmo. Para isso deve-se executar o arquivo **index.html**, localizado na pasta **visual**. Após isso, basta selecionar o arquivo desejado e será mostrado 2 gráficos, o primeiro somente com os dados sem nenhum clusterização, e o segundo com os dados clusterizados. Os triângulos representam os centroides. 
  </p>

## AGRADECIMENTOS

<p> Agradeço ao professor Felipe Coutinho pelos ensinamentos propostos na disciplina e pela disponibilidade e ajuda sempre que necessário. </p>