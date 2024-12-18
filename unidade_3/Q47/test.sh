A=0
B=100
EXECUTABLE="./main"

declare -a NS=("2000000000" "4000000000" "6000000000" "8000000000")
declare -a PS=("1" "2" "4")

OUTPUT_FILE="execution_times.txt"

> $OUTPUT_FILE

for N in "${NS[@]}"; do
    for P in "${PS[@]}"; do
        echo "Testing with n=$N, p=$P..." | tee -a $OUTPUT_FILE
        for i in {1..5}; do
            mpiexec -n $P $EXECUTABLE $A $B $N >> $OUTPUT_FILE
        done
        echo "" >> $OUTPUT_FILE
    done
done

echo "Testes concluídos! Resultados salvos em $OUTPUT_FILE."
