cmake_minimum_required (VERSION 2.6)
project (geneticexpression)

set( sources 
	src/Chromosome.cpp
	src/ChromosomeFactory.cpp
	src/ChromosomeFactory.h
	src/Chromosome.h
	src/ConsoleApplication1.cpp
	src/ExpressionEvaluator.cpp
	src/ExpressionEvaluator.h
	src/ExpressionToken.cpp
	src/ExpressionToken.h
	src/GenAlgRunner.cpp
	src/GenAlgRunner.h
	src/Gene.cpp
	src/GeneFactory.cpp
	src/GeneFactory.h
	src/Gene.h
	src/GeneticExpressionGenerator.cpp
	src/GeneticExpressionGenerator.h
	src/Logging.h
	src/Tester.cpp
	src/Tester.h
	src/TokenAdd.cpp
	src/TokenAdd.h
	src/TokenOperator.cpp
	src/TokenOperator.h
	src/TokenValue.cpp
	src/TokenValue.h
)

add_executable( genetic ${sources})

set_target_properties(genetic PROPERTIES COMPILE_FLAGS "-std=gnu++11")
