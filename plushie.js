let progressData = {
    Affection: 0,
    Rest: 0,
    Health: 0,
    Energy: 0
  };
  
  function increaseProgress(type) {
    if (progressData[type] < 100) {
      progressData[type] += 5; // Increase by 5%
      document.getElementById(`progress${type}`).style.width = progressData[type] + "%";
    }
  }
  
  function resetProgress(type) {
    progressData[type] = 0;
    document.getElementById(`progress${type}`).style.width = "0%";
  }