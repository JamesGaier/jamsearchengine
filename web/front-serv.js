async function handleSearchResults(query) 
{
    if (query === "")
    {
        return;
    }

    filteredQuery = new URLSearchParams({ q: query });

    const url = `http://localhost:3030/search?${filteredQuery.toString()}`;
    
    fetch(url)
        .then(response => response.json())
        .then(data => {
            displaySearchResults(data.Result);
        })
        .catch(error => {
            console.error(error);
        });
}


function displaySearchResults(data) 
{
    const parent = document.getElementById("search-results");

    // remove the previous search results
    while (parent.firstChild)
    {
        parent.removeChild(parent.lastChild);
    }

    if (data === "No search results found")
    {
        const li = document.createElement("li");
        const p =  document.createElement("p");
        p.innerText = data;
        li.appendChild(p);
        parent.appendChild(li);
        return;
    }

    for (const result of data)
    {
        const li = document.createElement("li");
        const a = document.createElement("a");
        li.classList.add("search-link");
        a.href = result;
        a.innerText = result;
        li.appendChild(a);
        parent.appendChild(li);
    }
}


window.onload = () => {

    const searchBar = document.getElementById("search-bar");
    const searchBtn = document.getElementById("search-btn");

    searchBtn.onclick = () => {
        handleSearchResults(searchBar.value)
    };

}

