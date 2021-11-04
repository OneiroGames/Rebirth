function update_modules()
{
  cd Engine/Source/ThirdParty/
  LINES=$(cat modules.txt | wc -l)
  for (( i=1; i <= LINES + 1; i++ ))
  do
    git clone --recurse-submodules $(sed -n "$i, 1p" modules.txt)
  done
  rm -f modules.txt
}

remove_garbage_in_modules()
{
  for dir in $(ls -d */);
  do
  {
    if [ $dir == "garbage_collector/" ]
    then
      continue
    fi

    cd garbage_collector/ && cd $dir/
    LINES=$(cat rmdirs.txt | wc -l)
    for (( i=1; i <= $LINES + 1; i++ ))
    do
    {
      DIRTORM=$(sed -n "$i, 1p" rmdirs.txt)
      cd .. && cd .. && cd $dir/ || exit
      rm -rf $DIRTORM
      cd .. && cd garbage_collector/ && cd $dir/ || exit
    }
    done

    LINES=$(cat rmfiles.txt | wc -l)
    for (( i=1; i <= $LINES - 1; i++ ))
    do
    {
      FILETORM=$(sed -n "$i, 1p" rmfiles.txt)
      cd .. && cd .. && cd $dir/ || exit
      rm -f $FILETORM
      cd .. && cd garbage_collector/ && cd $dir/ || exit
    }
    done
  }
  done
  cd .. && cd .. || exit
  rm -rf garbage_collector
}

function timer_start()
{
  time_start=$(date +%s.%N)
}

function timer_end()
{
  time_end=$(date +%s.%N)
  dt=$(echo "$time_end - $time_start" | bc)
}

function timer_print_result()
{
  LC_NUMERIC=C printf "Total runtime: %02.2f seconds\n" $dt
}

cd ..

echo "Cloning modules..."

timer_start
update_modules
timer_end

echo "Cloning modules completed."

timer_print_result

echo "Removing garbage in modules..."

timer_start
remove_garbage_in_modules
timer_end

echo "Removing garbage in modules was completed."

timer_print_result