From ubuntu:plucky

MAINTAINER jamesg

ENV VIRTUAL_ENV=/opt/venv 
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

ENV DB_PATH=/app/data/links.db3

WORKDIR /app

RUN apt-get update -y

RUN apt-get install -y  python3 python3-pip python3.13-venv

COPY web/ .

EXPOSE 5555
RUN python3 -m venv $VIRTUAL_ENV

RUN python3 -m pip install -r WebCrawlerBackendFlask/requirements.txt

CMD ["python", "-m", "gunicorn", "-w", "3", "-b", "0.0.0.0:5555", "WebCrawlerBackendFlask:app"]