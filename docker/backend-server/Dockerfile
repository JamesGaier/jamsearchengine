From ubuntu:plucky

MAINTAINER jamesg

ENV VIRTUAL_ENV=/opt/venv 
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

ENV DB_PATH=/app/data/links.db3

WORKDIR /app

RUN apt-get update -y

RUN apt-get install -y  python3 python3-pip python3.13-venv

COPY web/WebCrawlerBackendFlask/* .
EXPOSE 5555
RUN python3 -m venv $VIRTUAL_ENV

RUN python3 -m pip install -r requirements.txt

CMD ["flask", "--app", "backend", "run", "--host=0.0.0.0", "--port=5555"]